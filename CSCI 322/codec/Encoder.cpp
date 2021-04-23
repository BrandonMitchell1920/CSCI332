/*
 * Name:        Brandon Mitchell
 * Description: The implentation of the Encoder class, see it for a more
 *              detailed description.
 */

#include "Encoder.h"

// Outputs bit string to file, pads as necessary, assumes file already open
void Encoder::writeBits(std::ofstream & outFile, std::string theBits) const
{
    // Pad bits with enough bits to make it a multiple of eight, use this bit
    // string as my own bitset
    theBits += std::string(BITS - theBits.size() % BITS, '0');
    
    // Loop for the number of bytes
    for (unsigned long long i = 0; i < theBits.size() / BITS; i++)
    {        
        // Slice and convert to char
        char byte = std::stoi(theBits.substr(i * BITS, BITS), nullptr, 2);
        
        // Output to file handle passed in
        outFile.write(& byte, sizeof(byte));
    }
}

// Reads in the structure and create maps
void Encoder::readFile()
{
    std::ifstream inFile(fileName);
    
    if (inFile.good())
    {
        // The current line being read in
        std::string line;
        
        // For unrealistically large ASCII art
        unsigned long long total = 0, y = 0;
        
        // While there are lines to read ...
        while (std::getline(inFile, line))
        {
            for (unsigned long long x = 0; x < line.size(); x++)
            {
                // Get current value
                char value = line[x];
                
                if (!Encoder::printable(value))
                {
                    // Not a printable char or tab, newline, or carriage return
                    throw CodecExcept("File \"" + fileName + "\" contains "
                                      "non-printable ASCII values!  All ASCII "
                                      "values must be 9, 10, 13, or in the "
                                      "range [32, 126]!");
                }
                
                // Store the paired value with its char, convert char to 
                // encoded value later
                unsigned int temp = PairingFunction::pi(x, y);
                if (piMap.find(temp) != piMap.end())
                {
                    throw CodecExcept("Multiple values mapped to same key!  "
                                      "File may be too large to encode "
                                      "properly.");
                }
                else
                {
                    piMap.insert({temp, value});
                }
                
                // If the character is in the map
                if (symbolMap.find(value) != symbolMap.end())
                {
                    // Update its entry
                    symbolMap[value].count++;               
                }
                else
                {
                    // Insert character into map
                    symbolMap.insert({value, TableEntry{1, 0, ""}});
                }
            }
            
            // Update total
            total += line.size();
            
            // "Move" to next line
            y++;
        }
        
        // Loop to set all frequencies, use a reference in for so I don't have 
        // to do funky indexing :)
        for (auto & value : symbolMap)
        {
            // Cast to double due to integer division
            value.second.freq = (double) value.second.count / total;
        }
        
        // Make the tree and assign the codes!!!
        HuffmanCode(symbolMap);
        
        // Output the chars, their count, and code
        std::cout << "<char>\t<count>\t<code>\n";
        for (auto value : symbolMap)
        {
            std::cout << value.first << "\t" << value.second.count << "\t" <<
                value.second.code << std::endl;
        }
        
        // Close the file as to not take up memories
        inFile.close();
    }
    else
    {
        // Throw exception to let user know of issue
        throw CodecExcept("File \"" + fileName + "\" doesn't exist!  Make "
                          "sure the file is spelled correctly and in the "
                          "correct directory.");    
    }   
}

// Function to write the codeword
void Encoder::writeCWD() const
{
    // Slap on the codeword extension
    std::string newFile = fileName.substr(0, fileName.rfind(".")) + CWDEXT;
    
    // Create file in binary mode
    std::ofstream outFile(newFile, std::ios::binary);
    
    // Make sure file was able to be created sucessfully
    if (outFile.good())
    {
        // A string to hold the codes and then convert to bit set
        std::string tempBits;
        
        // Get and output total size, have to store in val to get memory 
        // address and output
        char size = symbolMap.size();
        outFile.write(& size, sizeof(size));
        
        // Proceed to output each symbol and its codeword length
        for (auto value : symbolMap)
        {
            // Need to store so they are lvalues
            std::string code = value.second.code;
            size = code.size();
            
            outFile.write(& value.first, sizeof(value.first));
            outFile.write(& size, sizeof(size));
            
            // Combine to output in bytes
            tempBits += code;
        }
        
        // Call function to output a bit string, will pad automatically
        Encoder::writeBits(outFile, tempBits);
        
        // Close file as we are done with it!
        outFile.close();
        
        // Inform user of file created
        std::cout << "Codeword file \"" + newFile + "\" created!\n";
    }
    else
    {
        // Throw exception to let user know of issue
        throw CodecExcept("File \"" + newFile + "\" could not be created!  "
                          "Make sure the directory is not write protected.");
        
    }
}

// Function to write the binary
void Encoder::writeBIN() const
{
    // Slap on the binary extension, if no ., then append to end, lets hope 
    // you can't have directories with . in them and then a file without . like
    // ~/csci.232/art or something or else this could be messy
    std::string newFile = fileName.substr(0, fileName.rfind(".")) + BINEXT;
    
    // Create file in binary mode
    std::ofstream outFile(newFile, std::ios::binary);
    
    // Make sure file was able to be created sucessfully
    if (outFile.good())
    {
        char groupSeperator = GROUP_SEP;
        unsigned int size = piMap.size();

        // Output signature, need to cast to char *
        outFile.write(reinterpret_cast<char *>(& magic::signature), 
            sizeof(magic::signature));
            
        // Group seperator symbol
        outFile.write(& groupSeperator, sizeof(groupSeperator));
        
        // Output the size of the piMap, which is the count of chars
        outFile.write(reinterpret_cast<char *>(& size), sizeof(size));
        
        // Another seperator
        outFile.write(& groupSeperator, sizeof(groupSeperator));
        
        // Output the piMap, the special values that tell us where each char 
        // goes in the final image
        for (auto value : piMap)
        {
            // Currently an unsigned long long, document says it should be 32
            // bits, so cast to int
            unsigned int pi = value.first;
            
            // Output with the casting
            outFile.write(reinterpret_cast<char *>(& pi), sizeof(pi));
        }
        
        // Yet another seperator, if we know the size of each field, why must
        // we seperate them?  Or is this just the formal way to do it?
        outFile.write(& groupSeperator, sizeof(groupSeperator));
        
        // Bit string to hold all codes in one
        std::string tempBits;
        
        // Slap all codes into one loooong bitstring
        for (auto value : piMap)
        {
            tempBits += symbolMap.at(value.second).code;
        }
        
        // Call function to parse bits and output
        Encoder::writeBits(outFile, tempBits);
        
        // Close file
        outFile.close();
        
        // Ouptut file and let user know of its name
        std::cout << "Encoded binary \"" + newFile + "\" created!\n";
    }
    else
    {
        // Throw exception to let user know of issue
        throw CodecExcept("File \"" + newFile + "\" could not be created!  "
                          "Make sure the directory is not write protected.");
    }
}

// Constructor for class
Encoder::Encoder(std::string fileName) : fileName(fileName)
{
    // Read file once created
    Encoder::readFile();
    Encoder::writeCWD();
    Encoder::writeBIN();
    
    std::cout << "Binary and codeword files must be in same directory when "
                 "decoded.\n";
}