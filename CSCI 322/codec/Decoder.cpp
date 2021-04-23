/*
 * Name:        Brandon Mitchell
 * Description: Implentation of the Decoder class, see it for a more detailed
 *              description.
 */
 
#include "Decoder.h"

// Confirm the signature is valid!  I tested it by modifying the signature in a
// hex editor, and they work fine!
void Decoder::signatureCheck(unsigned int signature)
{
    // Check the magic number, inform user of magic number mismatch
    if ((signature & magic::magicMask) != vMAGIC)
    {
        throw CodecExcept("Magic number mismatch!  Cannot decode binaries "
                          "written by different programs!  Your magic number "
                          "is " + std::to_string(signature & magic::magicMask)
                          + "and the program's is " + std::to_string(vMAGIC) + 
                          "!\n");
    }
    
    // Check the major version and inform user of different
    if ((signature & magic::majorMask) != (magic::signature & magic::majorMask))
    {
        unsigned int ourMajor = (signature & magic::majorMask) >> 28;
        throw CodecExcept("Major number mismatch!  Your major number is "
                          + std::to_string(ourMajor) + " and the number of "
                          "this program is " + std::to_string(vMAJOR) + "!");
    }
    
    // Check the minor version and inform user of different
    if ((signature & magic::minorMask) != (magic::signature & magic::minorMask))
    {
        unsigned int ourMinor = (signature & magic::minorMask) >> 20;
        throw CodecExcept("Minor number mismatch!  Your minor number is "
                          + std::to_string(ourMinor) + " and the number of "
                          "this program is " + std::to_string(vMINOR) + "!");
    }
}

// Reads in a file as a bitstring, assumes file is open
std::string Decoder::readBits(std::ifstream & inFile) const
{
    unsigned long long current, end, bytesSize;
    
    // Get current location, move cursor to end
    current = inFile.tellg();
    inFile.seekg(0, std::ios::end);
    
    // Get current location, use to find total size of bitstring
    end = inFile.tellg();
    bytesSize = end - current;
    
    // Use size of bitstring to return to former location
    inFile.seekg(-bytesSize, std::ios::end);
        
    // Store the bits in this bit string for slicing
    std::string bitString;
    
    // Read in bitstring one byte at a time, don't want to fiddle with
    // reading in the whole thing at once, may change later
    for (unsigned long long i = 0; i < bytesSize; i++)
    {
        // Byte being read in
        char readByte;
        inFile.read(& readByte, sizeof(readByte));
        
        // Add to bitstring to slice later
        bitString += std::bitset<BITS>(readByte).to_string();
    }
    
    return bitString;
}

// Construct the image from the char map
void Decoder::imageConstruct()
{
    for (auto value : charMap)
    {
        // Get the x and y from the pi value
        unsigned long long x = PairingFunction::x(value.first);
        unsigned long long y = PairingFunction::y(value.first);
        
        // Since the order of the x, y may not be exactly in order, pad image
        // on the y with vectors
        while (image.size() <= y)
        {
            image.push_back(std::vector<std::string>());
        }
        
        // Pad vector with empty strings until it can be inserted
        while (image[y].size() <= x)
        {
            image[y].push_back("");
        }
        
        // Set "pixel" of ASCII image to the char
        image[y][x] = value.second;
    }
}

// Function to read the codeword file
void Decoder::readCWD()
{
    // Slap on the codeword extension
    std::string newFile = fileName.substr(0, fileName.rfind(".")) + CWDEXT;
    
    std::ifstream inFile(newFile, std::ios::binary);
    
    if (inFile.good())
    {
        // Count of all characters, temp vars for adding to map
        char count, tempChar, tempLength;
        
        // Store the char and its length
        std::map<char, char> tempMap;
        
        // Read in number of symbols in the map
        inFile.read(& count, sizeof(count));
        
        // Read in each char and its code length
        for (char i = 0; i < count; i++)
        {
            inFile.read(& tempChar, sizeof(tempChar));
            inFile.read(& tempLength, sizeof(tempLength));
            
            // Store into temp map to parse bit string later
            tempMap.insert({tempChar, tempLength});
        }
        
        // Store the bits in this bit string for slicing
        std::string bitString = Decoder::readBits(inFile);
        
        // Index into the bitstring
        unsigned long long index = 0;
        
        for (auto value : tempMap)
        {           
            // The code being constructed
            std::string code;
            
            // Keep slapping chars onto the string while we havent't reached
            // the length of the code, padded zeroes ignored
            while (value.second)
            {    
                code += bitString[index++];
                value.second--;
            }
            
            // Add to code word map to use in decoding of binary
            codeWords.insert({code, value.first});
        }
        
        inFile.close();
    }
    else
    {
        // Throw exception to let user know of issue
        throw CodecExcept("File \"" + newFile + "\" doesn't exist!  Make sure "
                          "the binary's matching codeword file has the same "
                          "name and \"*.cwd\" extension!");
    }
}

// Function to read in the binary
void Decoder::readBIN()
{
    // Makes sure file has the proper extension, rfind so text.txt.in becomes
    // text.txt.bin and not text.bin
    std::string newFile = fileName.substr(0, fileName.rfind(".")) + BINEXT;
    
    std::ifstream inFile(newFile, std::ios::binary);
    
    if (inFile.good())
    {
        unsigned int signature, count;
        char groupSeperator;
        
        // Read in signature, check major, minor, magic numbers
        inFile.read(reinterpret_cast<char *>(& signature), sizeof(signature));
        Decoder::signatureCheck(signature);
        
        // Read in the group seperator symbol
        inFile.read(& groupSeperator, sizeof(groupSeperator));
        
        // Total count of characters in file and another group seperator
        inFile.read(reinterpret_cast<char *>(& count), sizeof(count));
        inFile.read(& groupSeperator, sizeof(groupSeperator));
        
        // Holds the pi map values until I need them, know size, set ahead of
        // time to optimize it
        std::vector<unsigned int> piHolder(count, 0);
        
        // Procede to read in all pi values
        for (unsigned int i = 0; i < count; i++)
        {
            // Create var and read in int
            unsigned int temp;
            inFile.read(reinterpret_cast<char *>(& temp), sizeof(temp));
            
            // Store into our piHolder to use later
            piHolder[i] = temp;
        }
        
        // Read the final group seperator
        inFile.read(& groupSeperator, sizeof(groupSeperator));
        
        // Read in the bits using private function
        std::string bitString = Decoder::readBits(inFile);
        
        // Close as we have all the data we need now
        inFile.close();
        
        // Index into bit string to parse
        unsigned long long index = 0;
        
        // If there are 10 pi values, then I must parse 10 codes from the 
        // string
        for (unsigned int i = 0; i < count; i++)
        {
            std::string temp;
            
            // Until a code word is found, add a new bit to string
            while (codeWords.find(temp) == codeWords.end())
            {
                temp += bitString[index++];
            }
            
            // Insert the pi value with its matching code word into charMap
            charMap.insert({piHolder[i], codeWords[temp]});
        }
    }
    else
    {
        // Throw error as we can't really recover from this easily or just 
        // ignore it, should not trigger due to file type check in main
        throw CodecExcept("File \"" + newFile + "\" doesn't exist!  Make sure "
                          "it is spelled correctly or in the proper "
                          "directory!");
    }
}

// Constructor, takes name of file
Decoder::Decoder(std::string fileName) : fileName(fileName)
{
    Decoder::readCWD();
    Decoder::readBIN();
    Decoder::imageConstruct();
}

// Converts vector image to a string
std::string Decoder::toStringImage() const
{
    std::string str;
    
    // Loop through each vector and add all strings together
    for (unsigned long long i = 0; i < image.size(); i++)
    {
        for (unsigned long long j = 0; j < image[i].size(); j++)
        {
            str += image[i][j];
        }
        
        // Need to add newline character as it isn't saved to file
        str += "\n";
    }
    
    return str;
}

// Outputs ASCII image to file, can simply return true or false as it is easy 
// to recover from this mistake
bool Decoder::writeImage(std::string newFile) const
{
    // Check default paramter value
    if (newFile == "")
    {
        newFile = fileName.substr(0, fileName.rfind(".")) + OUTEXT;
    }
    
    // Open file in text mode
    std::ofstream outFile(newFile);
    
    // Check if it is opened
    if (outFile.good())
    {
        // Simply call toString function and close
        outFile << Decoder::toStringImage();
        outFile.close();
        
        std::cout << "Image saved to \"" + newFile + "\"!\n";
        
        // Return true to let user know file was written sucessfully
        return true;
    }
    else
    {
        return false;
    }
}