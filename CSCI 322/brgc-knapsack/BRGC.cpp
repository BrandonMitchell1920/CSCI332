/**
 * Implementation of the BRGC class
 *
 * Phillip J. Curtiss, Associate Professor
 * pcurtiss@mtech.edu, 406-496-4807
 * Department of Computer Science, Montana Tech
 */
 
/*
 * Modified by: Brandon Mitchell
 * Descirption: Changed a function name since I added a new function with a 
 *              similar name.
 */

#ifndef BRGC_IMP
#define BRGC_IMP

#include "BRGC.h"

// Default constructor
BRGC::BRGC() {}

std::shared_ptr<std::list<std::string>> BRGC::calcPowerSet(unsigned int n)
{
    if (n == 1) // base case
        // return a list containing the only possible power-set from
	    // a single item; the empty-set (0), or the set containing
		// the one item
        L = std::make_shared<std::list<std::string> >(std::initializer_list<std::string>{"0", "1"});
    else
    {
        // holds the excluded and included sets from the powerset of this instance
        // from the previous instance of the solution
        std::list<std::string> L1, L2;

        // temporary list pointer referencing the list generate from the
        // previous instance of the problem; need a reference since we need
		// to reference the list multiple times
        std::shared_ptr<std::list<std::string> > tmpL;

        // obtain a reference to the power-set solution of the previous instance 
        // to the problem
        tmpL = calcPowerSet(n-1);

        // iterate through the list and add the items to L1 in forward order
        for_each (tmpL->begin(), tmpL->end(),
            [&L1](string item){L1.push_back(item);});

        // set L2 to have the same contents as L1, then reverse the order 
        L2 = L1;
        reverse(L2.begin(), L2.end());

        // create a new list to store the solution to this instance of the problem
        L = std::make_shared<std::list<std::string> >();

        // iterate over the list L1 - add the items to this instance solution
        // prepending a 0 to each element to represent non-inclusion of the 
        // additional item in this instance not being in the previous instance solution
        for(auto it = L1.begin(); it != L1.end(); it++)
            L->push_back("0" + *it);
        
        // iterate over the list L2 - add the items to this instance solution
        // preceeding a 1 to each element to represent inclusion of the additional
        // item in this instance not being in the previous instance solution
        for(auto it = L2.begin(); it != L2.end(); it++)
            L->push_back("1" + *it);
    } // end if

    // return a pointer to the powerset solution for this instance of the problem
    return (L);
} // end calcPowerSet

#endif