/**
 * CSCI332 - Design and Analysis of Algorithms
 * 
 * Represents a point in R^2
 * Implementation 
 * 
 * Phillip J. Curtiss, Associate Professor
 * pcurtiss@mtech.edu, 406-496-4807
 * Department of Computer Science, Montana Tech
 */

/*
 * Modified by: Brandon Mitchell
 * Description: Implementation of the Point class.
 */

#include <cstdio>		// For sprinf

#include "Point.h"

// Comparing floating point numbers, prevent funky errors
#define EPSILON 1E-6

// Default, non parameterized constructor
Point::Point() {}

// Parameterized constructor, takes x and y coords
Point::Point(double x, double y) : x(x), y(y) {}

// Parameterized constructor, takes in tuple and splits it up
Point::Point(std::tuple<double, double> point) : x(std::get<0>(point)), 
    y(std::get<1>(point)) {}

// toString function of point class
std::string Point::toString() const
{
    // Char buffer to hold string
    char buffer[100];
    
    // Format string, note 0 places after decimal
    sprintf(buffer, "(%.0f, %.0f)", x, y);
    
    // Convert to string and return, constructor parses automattically for '\0'
    return std::string(buffer);
}

// Overloaded == operator for checking for point equivalancy
bool Point::operator == (const Point & point) const
{
    // Subtract values from each other, if equal should be zero, but have to do
    // special check due to floating point errors
    double compX = this->x - point.x, compY = this->y - point.y;
    
    // Quick little absolute value
    if (compX < 0) {compX = -compX;}
    if (compY < 0) {compY = -compY;}
    
    // Return true if both are off by less than EPSILON
    return compX < EPSILON && compY < EPSILON;
}

// Overloaded != operator, simply not == operator
bool Point::operator != (const Point & point) const
{
    // Check for equivalancy and not it
    return !(* this == point);
}

// Overloaded < operator, compare x values, use to sort by x values
bool Point::operator < (const Point & point) const
{
    // Compare the ys to check equality
    double compY = this->y - point.y;
    
    // ys are equal
    if (compY < EPSILON)
    {
        // Compare xs
        return this->x < point.x;
    }
    else
    {
        // Want higest y first
        return this->y > point.y;
    }
}

// Overloaded = operator, assignment of a point to a point
Point & Point::operator = (const Point & point)
{
    // Set values of point and then return, need to return to chain assignment
    // statements together
    this->x = point.x;
    this->y = point.y;
    
    return * this;
}

// Friend function, overloaded << operator for outputing points
std::ostream & operator << (std::ostream & outStream, const Point & point)
{
    // Simply call the toString function and output that
    return outStream << point.toString();
}

// Calculates the distance a point is, this, from a line formed by two other
// points, point1, point2
double Point::lineDistance(const Point point1, const Point point2) const 
{
    // Calculate the distance
    double dist = (this->y - point1.y) * (point2.x - point1.x) - 
        (point2.y - point1.y) * (this->x - point1.x);
        
    // Absolute value of the distance
    if (dist < 0) {dist = -dist;}
    
    return dist;
}