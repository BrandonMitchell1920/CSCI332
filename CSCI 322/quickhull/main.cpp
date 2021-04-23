/**
 * CSCI332 - Design and Analysis of Algorithms
 * 
 * Quick Hull
 * divide and conquer strategy
 * 
 * Phillip J. Curtiss, Associate Professor
 * pcurtiss@mtech.edu, 406-496-4807
 * Department of Computer Science, Montana Tech
 */
 
/*
 * Modified by: Brandon Mitchell
 * Description: Implentated the render function.  It can render to std::cout 
 *              a file stream if the user requests (via command line arg).  
 *              If complied with "make OPTIONS=-DUSERANDOM", a random set of
 *              points is generated to test the Quickhull class.  Without
 *              this, a predefined set of points is used.
 */
 
#include <cstddef>      // Standard definitions
#include <cstdlib>      // Standard C++ Library
#include <iostream>     // Output to terminal
#include <string>       // Used in printing out info
#include <set>          // Set container for holding hull points
#include <vector>       // Holding all points
#include <cmath>        // For flooring doubles when comparing
#include <fstream>      // File streams, file I/O
#include <sstream>      // String stream, store grid until outputted
#include <algorithm>    // For std::find, set's find caused problems

#include <time.h>       // Seed srand with current time

#include "Point.h"      // Point class
#include "Quickhull.h"  // Qickhull class

#define POINT_SZ 20     // Number of random points
#define XEXTENT 35      // Maximum random x value
#define YEXTENT 23      // Maximum random y value

// Render points in a 2D graph
void render(std::vector<Point> points, std::set<Point> hull, 
    std::string fileName = "")
{
    // Save all data to stringstring, use in std::cout and in file output
    std::stringstream output;
    
    // Get the maximum x and y values to determine size of grid, only search 
    // the hull as it has to have the maxes, inner points can be ignored
    unsigned int xMax = 0, yMax = 0;
    for (Point point : hull)
    {
        // Save value if greater than current, floor for comparision, truncates
        // with assignemnt automatically
        if (std::floor(point.getX()) > xMax) {xMax = point.getX();}
        if (std::floor(point.getY()) > yMax) {yMax = point.getY();}
    }
    
    // Create grid for points, currently all empty spaces, in Python, strings
    // are immutable, so I forgot I could just treat them like any old array in
    // C++
    std::vector<std::string> grid(++yMax, std::string(++xMax * 2, ' '));
    
    // Add each point to the grid
    for (Point element : points)
    {
        // Normal set::find doesn't work as an ordered set is a tree and it 
        // the search differently and messes up because of it
        char marker = std::find(hull.begin(), hull.end(), element) != 
            hull.end() ? 'o' : '+';
        
        // Values truncate automatically
        unsigned int x = element.getX();
        unsigned int y = element.getY();
        
        // Set location to marker
        grid[y][x * 2] = marker;
    }
    
    // For labeling y axis, use to calculate padding
    unsigned int yDigits = std::to_string(yMax).size();
    
    // First line, has no points, simply for making graph look nicer
    output << std::to_string(yMax) + "|\n";
    
    // Count down to flip the graph, (0, 0) at top instead of bottom, signed
    // because it will go negative
    for (signed int i = yMax - 1; i >= 0; i--)
    {
        // x label and the vertical bar, pad with spaces to keep aligned, then
        // slap on the grid and the newline char
        output << std::string(yDigits - std::to_string(i).size(), ' ') +
            std::to_string(i) + "| " + grid[i] + "\n";
    }
    
    // Horizontal line at bottom of graph, space inbetween each character to 
    // look nice, have to multiply by two as such
    output << std::string(yDigits, ' ') + "+" + std::string(xMax * 2 + 2, '-') 
        + "\n";
    
    // Number of digits in xMax, used in labeling the x axis
    unsigned int xDigits = std::to_string(xMax).size();
    
    // Label for x axis, modify with labels and then output
    std::vector<std::string> xAxis(xDigits, std::string(xMax * 2 + 1, ' '));
        
    // Insert the x labels in to the xAxis vector
    for (unsigned int i = 0; i <= xMax; i++)
    {
        std::string num = std::to_string(i);
        
        // Index into string and walk down vector to fill vertically, i * 2 
        // due to space for padding and looking nice
        for (unsigned int j = 0; j < num.size(); j++)
        {
            xAxis[j][i * 2] = num[j];
        }       
    }
    
    // Output the xAxis
    for (std::string str : xAxis)
    {
        // Padd with spaces first, then add string
        output << std::string(yDigits + 2, ' ') + str + "\n";
    }
    
    // Convert stringstream to string and output like normal
    std::cout << output.str();
    
    // Default parameter check
    if (fileName != "")
    {
        // Create file handle
        std::ofstream fileOut(fileName);
        
        // Check file is open, should make a new one automatically, but just
        // in case
        if (fileOut.is_open())
        {
            // Output like above and close file, which I forgot to do in the 
            // last assigment after reading it in, whoops
            fileOut << output.str();
            fileOut.close();
        }
        else
        {
            // Error message so user knows their beautiful plot wasn't saved
            std::cout << "\nError saving plot to " + fileName + "!\n";
        }
    }
}

// Command line arguments for main, argc is number of arguments, first is the
// executible, argv is a char array of char arrays, or a char ptr to char ptrs
int main(int argc, char * * argv)
{
    
// Value defined at compile time when make is called
#ifdef USERANDOM

    // Seed the randomness with the current time
    std::srand(time(NULL));

    // Generate random points based on predefined limits
    std::vector<Point> points;
    for (int i = 0; i < POINT_SZ; i++)
    {  
        points.push_back(Point(std::rand() % XEXTENT, std::rand() % YEXTENT));
    }

// USERANDOM not defined
#else
    
    // Predefined set of points to test on
    std::vector<Point> points = {{1, 6}, {4, 15}, {7, 7}, {10, 13}, {11, 6}, 
        {11, 18}, {11, 21}, {12, 10}, {15, 18}, {16, 6}, {18, 3}, {18, 12}, 
        {19, 15}, {22, 19}};
        
#endif

    // Quickhull instance
    Quickhull hull(points);

    // Output the points that are part of the problem
    std::cout << "The points that are part of the problem are:\n";
    for (Point point : points)
    {
        std::cout << "  " << point;
    }
    std::cout << std::endl;

    // Compute the convex hull of the points
    std::set<Point> result = hull.getHull();

    // If there is no hull, inform user, else call render and graph the points
    if (result.empty())
    {
        std::cout << "There is no hull for the set of points provided.\n";
    }
    else
    {
        // Output the points on the hull
        std::cout << "The points forming the hull include:\n";
        for (Point point : result)
        {
            std::cout << "  " << point;
        }
        std::cout << std::endl;

        // If user gave an output file in the command line, numArgs is two,
        // convert to string and give to render function
        render(points, result, argc > 1 ? std::string(argv[1]) : "");
    } 
    
    std::cout << "Note that points have been truncated to be plotted in the "
                 "terminal and the values shown may not be accurate.\n";
    
    return EXIT_SUCCESS;
}