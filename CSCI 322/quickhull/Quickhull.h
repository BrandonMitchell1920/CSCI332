/**
 * CSCI332 - Design and Analysis of Algorithms
 * 
 * Quickhull class to compute convex hull
 * Using divide and conquer strategy
 * 
 * Phillip J. Curtiss, Associate Professor
 * pcurtiss@mtech.edu, 406-496-4807
 * Department of Computer Science, Montana Tech
 */
 
/*
 * Modified by: Brandon Mitchell
 * Description: The declaration of the Quickhull class.  Class takes in a 
 *              vector of points and finds points on the exterior and adds them
 *              to the hull.  It does this automatically upon being created
 *              (user doesn't call a function to initiate it). Function to 
 *              find which side a point is on is included.
 */

#pragma once

#include <vector>   // Storing points
#include <set>      // Storing the resultant hull

#include "Point.h"  // Point class that will make up the hull

#define RIGHT -1    // Left of the line 
#define SAME 0      // Colinear
#define LEFT 1      // Right of the line

class Quickhull
{
    private:
    
        // Collection of points in the problem
        std::vector<Point> points;
        
        // Points that will make up the hull
        std::set<Point> hull;

        /**
         @brief     Constructs the hull by find max points of each line 
                    segment, recursive function
         @param     leftPoint: Point, the left side of the line
         @param     rightPoint: Point, the right side of the line
         @param     side: signed int, a value indicating the side we are 
                    looking at
         @post      hull attribute will be modified
         */
        void convexHull(Point leftPoint, Point rightPoint, signed int side);

        /**
         @brief     Finds the min and max points and then calles convexHull on
                    both halves
         @post      hull attribute will be modified after convexHull is called
         */
        void hullRecurse(); 

        /**
         @brief     Returns -1, 0, or 1 to signify which side the point is on
                    considering the line formed by point1 and point2
         @param     point1: Point, one of the points forming the line
         @param     point2: Point, one of the points forming the line
         @param     point: Point, the point that is on one side of the line 
                    formed by point1 and point2
         @return    signed int -1, 0, 1 indicating the side point is on
         */
        signed int findSide(Point point1, Point point2, Point point) const;

    public:
    
        /**
         @brief     Parameterized constructor
         @param     points: std::vector<Point>, a vector of points that will 
                    be considered for the hull
         @post      points attribute will be initialized to points vector param
         @return    A Quickhull instance
         */
        Quickhull(std::vector<Point> points);

        /**
         @brief     Getter for the hull
         @return    std::set<Point>, the hull
         */
        inline std::set<Point> getHull() const {return hull;}
};