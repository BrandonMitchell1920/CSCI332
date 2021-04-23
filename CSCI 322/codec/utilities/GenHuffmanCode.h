/**
 * CSCI 332 Design and Analysis of Algorithms
 * 
 * Huffman Image D/Encode
 * (and Hashing)
 * 
 * Phillip J. Curtiss, Associate Professor
 * pcurtiss@mtech.edu, 406-496-4807
 * Department of Computer Science, Montana Tech
 */
 
/*
 * Modified by: Brandon Mitchell
 * Description: Slapped some of the Huffman code together into this file.
 */

#pragma once

#include <string> // for Huffman Code
#include <memory> // shared pointers
#include <cstdlib> // standard c++ routines
#include <vector> // underlying storage for priority queue
#include <queue> // priority queue routines
#include <map> // associative container

using std::map;
using std::string;
using std::shared_ptr;
using std::make_shared;
using std::priority_queue;
using std::vector;

#define SENTINEL '\035' // symbol not in input stream - choose carefully

// value structure for the huffman code table
// C++ compiler complains about anonymous structs, so we name it
struct TableEntry
{
    uint count; // the instances of a alphabet symbol
    double freq; // the count/total_of_all_symbol_instances
    string code; // the huffman codeword 
}; 

/**
 * MinHeapNode type
 */
struct MinHeapNode
{
    char symbol; // symbol from SymbolMap or sentinel
    double freq; // priority value for MinHeap

    shared_ptr<MinHeapNode> left; // left child tree node
    shared_ptr<MinHeapNode> right; // right child tree node

    // constructor for type
    MinHeapNode(char symbol, double freq) : symbol(symbol),
                                           freq(freq),
                                           left(nullptr),
                                           right(nullptr)
    {
    }
}; // end MinHeapNode

/**
 * Comparator for Priority Queue
 * generate priority based on MinHeapNode frequency
 */
using compare = struct {
    bool operator() (shared_ptr<MinHeapNode> lhs, 
                     shared_ptr<MinHeapNode> rhs)
    {
        // compare frequency values for priority order
        return (lhs->freq > rhs->freq);
    } // end invocation operator
}; // end compare

void HuffmanCode(map<char, TableEntry>&);