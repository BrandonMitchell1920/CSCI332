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
 * Description: Implementation of the Quickhull class.
 *
 */

#include "Quickhull.h"

// Recursively constructs the hull
void Quickhull::convexHull(Point leftPoint, Point rightPoint, signed int side)
{
    // Default index value, negative to check if valid
    signed long long index = -1;
    
    // Current max distance between points
    double maxDist = 0;
    
    for (unsigned long long i = 0; i < points.size(); i++)
    {
        double temp = points[i].lineDistance(leftPoint, rightPoint);
        
        // Farther away and on the correct side ...
        if (Quickhull::findSide(leftPoint, rightPoint, points[i]) == side &&
            temp > maxDist)
        {
            // Update index and maxDist
            index = i;
            maxDist = temp;
        }
    }
    
    // Index is invalid, no other points outside
    if (index == -1)
    {
        // Add both points to set
        hull.insert(leftPoint);
        hull.insert(rightPoint);
    }
    else
    {
        // Check each new chuck of hull
        Quickhull::convexHull(points[index], leftPoint, 
            -Quickhull::findSide(points[index], leftPoint, rightPoint));
        Quickhull::convexHull(points[index], rightPoint, 
            -Quickhull::findSide(points[index], rightPoint, leftPoint));
    }
}

// Calls recursive convexHull on each half
void Quickhull::hullRecurse()
{
    // Default min, max
    Point min = points[0], max = points[0];
    
    // Linear search for min and max
    for (unsigned int i = 0; i < points.size(); i++)
    {
        if (min.getX() > points[i].getX()) {min = points[i];}
        if (max.getX() < points[i].getX()) {max = points[i];}
    }
    
    // First do top half and then bottom half
    Quickhull::convexHull(min, max, LEFT);
    Quickhull::convexHull(min, max, RIGHT);
}

// Finds out which side of the line formed by point1 and poin2 point is on
signed int Quickhull::findSide(Point point1, Point point2, Point point) const
{
    // Calculate the distance using determinant
    double dist = 
        (point.getY()  - point1.getY()) * (point2.getX() - point1.getX()) - 
        (point2.getY() - point1.getY()) * (point.getX()  - point1.getX()); 
    
    // Sign determines which side the point is on
    if (dist > 0) {return LEFT;}
    else if (dist < 0) {return RIGHT;}
    else {return SAME;}
}

// Constructor of class, calls hullRecurse to find hull
Quickhull::Quickhull(std::vector<Point> points) : points(points) 
{
    Quickhull::hullRecurse();
}