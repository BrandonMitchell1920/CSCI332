/*
 * Name:        Brandon Mitchell
 * Description: The Encoder class!  Takes in the name of a file to encode and 
 *              reads in the data, constructing the symbolMap and piMap in the 
 *              process.  From there, it writes the cwd file and the bin file.
 *              The names of these files is based on the fileName passed in.
 *              Like Decoder, I had trouble with the overall design.  I think
 *              the way I did it is fine, but I know it could be a bit better.
 */

#pragma once

// A bunch of includes, #defines, and a custom exception
#include "CodecExcept.h"

class Encoder
{
    private:
    
        // The name of the file being encoded
        std::string fileName;

        // The map of pi values to their respective chars
        std::map<unsigned long long, char> piMap;
        
        // The map of chars in the image to their TableEntry, a struct of their
        // count, frequency, and codeword
        std::map<char, TableEntry> symbolMap;
        
        /**
         @brief     Returns a bool indicating if an ASCII char is printable
         @param     value: char, the ASCII value in question
         @return    bool, true if value is printable character, false otherwise
         */
        static inline bool printable(char value)
        {
            // There is a YouTube video (I don't remember who the author is)
            // in which the author attempts to make a program that can be
            // printed out, so the final executible has to be of all printable
            // chars
            return (value >= 32 && value <= 126) || value == 9 || value == 10 
                || value == 13;
        }
        
        /**
         @brief     Writes a bitstring out to file
         @param     outFile: std::ofstream reference, the file handle that the
                    bitstring is to be outputted to
         @param     theBits: std::string, the bitstring to be written to file
         @post      outFile will have its cursor at the end of file when done
         */
        void writeBits(std::ofstream & outFile, std::string theBits) const;
        
        /**
         @brief     Reads in the fileName and creatse the piMap and symbolMap
         @pre       Assumes fileName has been set
         @post      Sets the piMap and symbolMap
         @throws    CodecExcept if file doesn't exist, file contains non 
                    printable chars, or if file is too large and multiple same
                    keys are made
         */
        void readFile();
        
        /**
         @brief     Writes the codeword file to a binary file
         @throws    CodecExcept if file can't be written
         */
        void writeCWD() const;
        
        /**
         @brief     Writes the binary output file to a binary file
         @throws    CodecExcept if file can't be written
         */
        void writeBIN() const;        
    
    public:
    
        /**
         @brief     Constructor for the Encoder class
         @param     fileName: std::string, the name of the file to be encoded
         @post      Sets the fileName, calles readFile, writeCWD, writeBIN
         */    
        Encoder(std::string fileName);
};