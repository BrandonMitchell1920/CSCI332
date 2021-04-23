/**
 * CSCI 332 Design & Analysis of Algorithms
 * 
 * Project: Huffmain Image CODEC
 * 
 * Phillip J. Curtiss, Associate Professor
 * pcurtiss@mtech.edu, 406-496-4807
 * Department of Computer Science, Montana Tech
 */
 
#pragma once
 
#include <cstdint>

/*
 * Cantor Pairing Function Class
 */
class PairingFunction
{
    public:
        // return a diagonalized map from the indepdentent x,y coordinate
        static uint64_t pi(const uint64_t x, const uint64_t y);

        // given a diagonalized representation of a 2D coord, 
        // return the x-component
        static uint64_t x(const uint64_t pi);

        // given a diagonalized representation of a 2D coord,
        // return the y-component
        static uint64_t y(const uint64_t pi);
}; // end PairingFunction class