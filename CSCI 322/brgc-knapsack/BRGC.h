/**
 * Compute the Binary Reflected Gray Code for a given positive integer n 
 * using the minimal-change decrease-and-conquer by a constant approach 
 * return a smart pointer to the power set
 *
 * Phillip J. Curtiss, Associate Professor
 * pcurtiss@mtech.edu, 406-496-4807
 * Department of Computer Science, Montana Tech
 */
 
/*
 * Modified by: Brandon Mitchell
 * Description: Added in a function to return the pointer L without doing any
 *              calcualations.  If the number of problems has not increased, we
 *              can reuse the powerset.  When we change the bag's weight, the 
 *              problem needs to be recaluated, but we don't need to recaluate
 *              the powerset as it should still work for the problem. 
 */
 
#ifndef BRGC_H
#define BRGC_H

#include <list> // stl list ADT
#include <string> // stl string ADT
#include <cstdlib> // standard C++ library prototypes
#include <memory> // smart pointer prototypes
#include <algorithm> // algorithms for std ADTs that support iterators
#include <initializer_list> // initializer list; used by some of the stl ADTs

// namespace import for smart pointers
using std::shared_ptr;
using std::make_shared;

// namespace import for algorithms
using std::reverse;
using std::for_each;

// namespace import for stl data structures
using std::list;
using std::string;
using std::initializer_list;

class BRGC 
{
    private:
        // holds solution to this instance of the problem
        std::shared_ptr<std::list<std::string>> L;

    public:
        // default constructor
        BRGC();

        // return the power-set of n using the BRGC algorithm
        std::shared_ptr<std::list<std::string>> calcPowerSet(unsigned int n);
        
        // Returns the pointer L without doing calculations
        inline std::shared_ptr<std::list<std::string>> getPowerSet() const
        {
            return L;
        }            
};

#endif