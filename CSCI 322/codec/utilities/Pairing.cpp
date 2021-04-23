/**
 * CSCI 332 Design & Analysis of Algorithms
 * 
 * Project: Huffmain Image CODEC
 * 
 * Phillip J. Curtiss, Associate Professor
 * pcurtiss@mtech.edu, 406-496-4807
 * Department of Computer Science, Montana Tech
 */
#include <cstdint>
#include <cmath>

// Pairing Function Class
#include "Pairing.h"

// Calculate the diagonalized represnetation of a 2D Coordinate
uint64_t PairingFunction::pi(const uint64_t x, const uint64_t y)
{
    uint64_t s1 = x + y;
    uint64_t s2 = s1 + 1;
    uint64_t t = s1*s2;
    uint64_t pi = 0.5*(t) + y;

    // return the result
    return pi;
} // end PairingFunction

// Calculate the X-Coordinate from a diagonalized representation 
// of a 2D coordinate
uint64_t PairingFunction::x(const uint64_t pi)
{
    uint64_t w = floor(0.5*(sqrt(8*pi + 1) -1));
    uint64_t t = 0.5*(w*(w+1));
    uint64_t y = pi - t;
    uint64_t x = w - y;

    // return the result
    return x;
} // end x-coordinate

// Calculate the Y-Coordinate from a diagonalized representation
// of a 2D coordinate
uint64_t PairingFunction::y(const uint64_t pi)
{
    uint64_t w = floor(0.5*(sqrt(8*pi + 1) -1));
    uint64_t t = 0.5*(w*(w+1));
    uint64_t y = pi - t;

    // return the result
    return y;
} // end y-coordinate
