/**
 * CSCI332 Design and Analysis of Algorithms
 * 
 * Huffman Image CODEC
 * 
 * Phillip J. Curtiss, Associate Professor
 * pcurtiss@mtech.edu, 406-498-5679
 * Department of Computer Science, Montana Tech
 */
 
/*
 * Modified by: Brandon Mitchell
 * Description: Added a file type check and code to call Encoder or Decoder as
 *              necessary.
 */

#include <iostream>     // For I/O to console
#include <cstdlib>      // Standard C++ library routines
#include <fstream>      // File streams, reading / writing files
#include <string>       // Names of files

#include "CodecExcept.h"    // Contains some #defines, custom error
#include "magic/magic.h"    // Signature of binary file
#include "Encoder.h"        // The Encoder class
#include "Decoder.h"        // The Decoder class

// Function to check if file should be encoded or decoded, would ideally pass
// still open file to constructor of class, but ...
bool encodeOrDecode(std::string fileName)
{
    std::ifstream inFile(fileName, std::ios::binary);
        
    if (inFile.good())
    {
        unsigned int count;
        char groupSep;
        
        // Skip over size of signature, only need to check positions of the 
        // group seperators and if they exist
        inFile.seekg(sizeof(magic::signature), std::ios::cur);
        
        // This should be the group seperator, if it isn't, then this isn't a
        // encoded image binary, also check for end of file
        inFile.read(& groupSep, sizeof(groupSep));
        if (groupSep != GROUP_SEP || inFile.eof()) {return true;}
        
        // This should be the count, if it is, then a group seperator is count
        // ints away
        inFile.read(reinterpret_cast<char *>(& count), sizeof(count));
        
        // Check for next group seperator
        inFile.read(& groupSep, sizeof(groupSep));
        if (groupSep != GROUP_SEP || inFile.eof()) {return true;}
        
        // Move forward as necessary, don't read as we don't need to 
        inFile.seekg(count * sizeof(count), std::ios::cur);
        
        // Final check, if it fails, assume ASCII art and encode
        inFile.read(& groupSep, sizeof(groupSep));
        if (groupSep != GROUP_SEP || inFile.eof()) {return true;}
        
        inFile.close();
    }
    else
    {
        // Message to user who messed up big time
        std::cerr << "File \"" << fileName << "\" not found!  Make sure it "
                     "exists and is the proper directory!\n";
                     
        // Simply end program, could throw an error, but its not like this 
        // should be caught and dealt with in this context, would return if I
        // put this check in main, anyways, not throw an error
        exit(EXIT_FAILURE);
    }
    
    // If it passes the above checks, it means we need to decode it
    return false;
}

// Main function, can take a command line argument that is the file we are 
// looking to encode or decode
int main(int argc, char * * argv)
{   
    // If user didn't include the file to be converted ...
    if (argc < 2)
    {
        // ... inform them and end program with failure
        std::cerr << "Be sure to include file name!\n"
                     "<executible> <file name>\n";
        return EXIT_FAILURE;
    }
    else
    {        
        // Check the type of file first
        if (encodeOrDecode(std::string(argv[1])))
        {
            std::cout << "Beginning encoding ...\n";
            
            // Since the class throws errors in certain situations, I want to 
            // catch them and tell the user of the problem
            try
            {
                Encoder encoder = Encoder(std::string(argv[1]));
            }
            catch (CodecExcept & err)
            {
                std::cerr << "Error encountered while encoding!\n  what(): " + 
                             err.what() << std::endl;
                return EXIT_FAILURE;
            }
        }
        else
        {   
            std::cout << "Beginning decoding ...\n";
    
            try
            {
                Decoder decoder = Decoder(std::string(argv[1]));
                
                decoder.writeImage();
                std::cout << decoder.toStringImage();
            }
            catch (CodecExcept & err)
            {
                std::cerr << "Error encountered while decoding!\n  what(): " + 
                             err.what() << std::endl;
                return EXIT_FAILURE;
            }
        }
    }

    // Return 0 to indicate program ran fine
    return EXIT_SUCCESS;
}