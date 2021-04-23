/**
  Huffman Image Codec
  magic number for binary encoded image files
  Requires -std=c++17 for CFLAGS

  Phillip J. Curtiss, Associate Professor
  pcurtiss@mtech.edu, 406-496-4807
  Department of Computer Science, Montana Tech
 */
 
#pragma once 
 
#include <cstdint> // unsigned int 32-bits wide

namespace magic // avoid variable name collissions
{
    // signature as follows: 
    // high-order 4 bits - define major version of codec
    // next 8 bits - define minor version of codec
    // next 20 bits - define magic number for codec
	inline std::uint32_t signature = 0xA15C0DEC;

	inline std::uint32_t majorMask = 0xF0000000; // major bitmask
	inline std::uint32_t minorMask = 0x0FF00000; // minor bitmask
	inline std::uint32_t magicMask = 0x000FFFFF; // magic bitmask
} // namespace

// macro for extracting MAJOR number from signature
#define vMAJOR ((magic::signature & magic::majorMask) >> 28)

// macro for extracting MINOR number from signature
#define vMINOR ((magic::signature & magic::minorMask) >> 20)

// macro for extracting MAGIC number from signature
#define vMAGIC  (magic::signature & magic::magicMask)

