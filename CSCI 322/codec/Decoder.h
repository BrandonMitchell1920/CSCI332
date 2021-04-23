/*
 * Name:        Brandon Mitchell
 * Description: The Decoder class!  Takes the name of a file and then goes from
 *              there!  I have it call the necessary functions in order in the 
 *              constructor.  Passing it an open file would be best as I open
 *              it in main, and I/O is expensive, but I believe this is fine.
 *              Also, I would make this just a bunch of loose functions as I 
 *              don't feel like a class is really needed, but the functions all
 *              need some shared data.  I could make one big function, but that
 *              is a worse solution than just using a class.  Sorry, I had a 
 *              little trouble with deciding on the designe on this one.
 */

#pragma once

// A bunch of includes, #defines, and a custom exception
#include "CodecExcept.h"

class Decoder
{
    private:
    
        // The name of the binary file passed in
        std::string fileName;
        
        // A 2D matrix that forms the image
        std::vector<std::vector<std::string>> image;
        
        // A map of the codewords and the chars they represent
        std::map<std::string, char> codeWords;
        
        // A map of the pi value and its respective char
        std::map<unsigned int, char> charMap;
        
        /**
         @brief     Compares the signature of the file with the signature in 
                    magic.h and throws an error if there is a mismatch
         @param     signature: unsigned int, the signature being checked
         @throws    CodecExcept if any mismatch is detected
         */
        static void signatureCheck(unsigned int signature);
        
        /**
         @brief     Reads a number of bytes from a file into a bitstring
         @param     inFile: std::ifstream reference, the file to be read from
         @pre       Assumes inFile is open and has its cursor at the beginning
                    of the bitstring to be read in
         @post      inFile's cursor will be at end of file
         @return    std::string, a bitstring consisting of the bytes read from
                    inFile
         */
        std::string readBits(std::ifstream & inFile) const;
        
        /**
         @brief     Using the charMap, constructs the image by expaning the 
                    2D matrix image as necessary
         @pre       Assumes the charMap has already been constructed
         @post      image will be modified to contain the original ASCII art
         */        
        void imageConstruct();
        
        /**
         @brief     Reads in the codeword data, adds CWDEXT to fileName and 
                    opens it
         @post      The codeWords map will have been constructed
         @throws    CodecExcept if file doesn't exist
         */        
        void readCWD();
        
        /**
         @brief     Reads in the binaray data from the fileName passed in the 
                    constructor
         @pre       codeWords must have already been constructed
         @post      The charMap will have been constructed
         @throws    CodecExcept if file doesn't exist
         */        
        void readBIN();
        
    public:
    
        /**
         @brief     Constructor for the Decoder class
         @param     fileName: std::string, the encoded binary to be opened
         @post      Reads in CWD, then BIN, then constructs image
         */        
        Decoder(std::string fileName);
    
        /**
         @brief     Converts the 2D image into a string that can be printed
         @return    std::string, the image that was converted
         */
        std::string toStringImage() const;
        
        /**
         @brief     Saves the image to a text file
         @param     newFile: std::string, the file to save the image to,
                    defaults to base fileName with OUTEXT added
         @return    bool, tells whether the writing sucdeeded or failed
         */                
        bool writeImage(std::string newFile = "") const;
};