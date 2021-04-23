/**
 * CSCI332 - Design and Analysis of Algorithms
 * 
 * Represents a point in R^2
 * 
 * Phillip J. Curtiss, Associate Professor
 * pcurtiss@mtech.edu, 406-496-4807
 * Department of Computer Science, Montana Tech
 */

/*
 * Modified by: Brandon Mitchell
 * Description: The declaration of the Point class.  Represents a point in the 
 *              2D plane and has a x and y coordinate.  Methods to determine
 *              distance from other points, compare points, and output point to
 *              a stream are included.
 */

#pragma once

#include <iostream>     // For << operator overload
#include <string>       // For to_string method
#include <tuple>        // Constructor from list of points

class Point
{
    private:
        
        // x and y coordinate of point, doubles for accuracy
        double x, y;

    public:
        
        /**
         @brief     Non-parameterized constructor
         @return    A Point instance with x = 0, y = 0
         */
        Point();
        
        /**
         @brief     Parameterized constructor
         @param     x: double, the x coordinate
         @param     y: double, the y coordinate
         @post      x, y are initialized to the values passed in
         @return    A Point instance
         */        
        Point(double x, double y);
        
        /**
         @brief     Parameterized constructor
         @param     point: std::tuple<double, double>, the container that will
                    be split up to make the x and y coordinate
         @post      x, y are initialized to the values in the tuple
         @return    A Point instance
         */
        Point(std::tuple<double, double> point);

        /**
         @brief     Returns the distance from this to the line formed by two 
                    points
         @param     point1: const Point, one of the points forming the line
         @param     point2: const Point, one of the points forming the line
         @return    double, the distance of this to the line formed by the
                    other two points
         */
        double lineDistance(const Point point1, const Point point2) const;

        /**
         @brief     Converts the Point instance to a string, truncates values 
                    so they look nice
         @return    An string instance of the Point
         */
        std::string toString() const;

        /**
         @brief     Determines if two points are equal
         @param     point: const Point &, the point being compared
         @return    bool value stating if points are equal
         */
        bool operator == (const Point & point) const;
        
        /**
         @brief     Determines if two points are not equal, simply nots ==
         @param     point: const Point &, the point being compared
         @return    bool value stating if points are not equal
         */
        bool operator != (const Point & point) const;
        
        /**
         @brief     Determines if this is less than other point
         @param     point: const Point &, the point being compared
         @return    bool value stating if this is less than other point
         */        
        bool operator < (const Point & point) const;
        
        /**
        @brief     Sets this equal to other point
        @param     point: const Point &, the point this will be set equal to
        @post      this will have its value modified
        @return    this, the point that has been modified
         */       
        Point & operator = (const Point & point);
        
        /**
        @brief     Outputs the point to the stream object, friend method
        @param     outStream: std::ostream &, the stream object
        @param     point: const Point &, the point being outputted
        @post      outStream will have its value modified with the Point object
        @return    The outStream object that has been modified
         */  
        friend std::ostream & operator << (std::ostream & outStream, 
            const Point & point);
        
        /**
         @brief     Returns the x value of the Point
         @return    double, the x value of the Point
         */  
        inline double getX() const {return x;}
        
        /**
         @brief     Returns the y value of the Point
         @return    double, the y value of the Point
         */
        inline double getY() const {return y;}
};