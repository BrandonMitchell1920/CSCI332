/*
 * Name:        Brandon Mitchell
 * Description: Includes a custom expception for my Encoder and Decorder.  Also
 *              includes a bunch of #defines and includes needed by the 
 *              classes.
 */

#pragma once

#include <stdexcept>    // For the custom exception below
#include <iostream>     // Printing out the names of file to user
#include <fstream>      // For file streams
#include <vector>       // Holding pi values until needed
#include <string>       // Names of file, bitstrings
#include <bitset>       // Converting binary values to bitstrings
#include <map>          // Mapping pi values to chars, chars to codewords

#include "utilities/GenHuffmanCode.h"   // The Huffman code generator
#include "utilities/Pairing.h"          // Cantor's Pairing Function routines
#include "magic/magic.h"                // The signature

// Just in case I want to quickly change the extensions
#define CWDEXT ".cwd"
#define BINEXT ".bin"
#define OUTEXT ".out"

// Group seperator symbol in ASCII
#define GROUP_SEP 29

// Shows up a ton, so I though using this is clearer than just a literal value
#define BITS 8

// Custom exception inherits from runtime_error
class CodecExcept : std::runtime_error
{
    public:
        
        /**
         @brief     Constructor for the exception, calls parent's constructor
         @param     message: std::string, the reason for the error
         */
        CodecExcept(std::string message = "") : std::runtime_error(message) {}
        
        /**
         @brief     Returns what caused the error
         @return    std::string, the reason for the error being thrown
         */
        inline std::string what() {return std::runtime_error::what();}
};