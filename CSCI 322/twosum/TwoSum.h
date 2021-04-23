/*
 * Name:    Brandon Mitchell
 * Description: Declaration of TwoSum class.  Stores nums, a target, and can
 *              calculate the two sum problem.  The user can then access the 
 *              SumExists variable to see what the result is.  Only calculates
 *              when modified.
 */

#pragma once

#include <vector>           // For nums vector
#include <algorithm>        // For find function
#include <unordered_map>    // For the solve function
#include <string>           // For toString function

class TwoSum
{
    private:
    
        // The target we are looking for
        signed long long target;
        
        // The vector that will store all the nums we want to look at
        std::vector<signed long long> nums;
        
        // A variable that will store the answer so it doesn't need to be 
        // recalculated each time, is updated whenever solve is called
        bool sumExists;

        /**
         @brief     Searches nums vector to see if any two numbers add to the 
                    target, is linear in nature, terminates early if found
         @post      The value of sumExists is updated
         */
        void solve();
            
    public:
    
        /**
         @brief     Constructor for class
         @param     target: signed long long, stores the sum we are looking for
         @param     nums: vector<signed long long>, stores the nums that are 
                    checked for a particular sum
         @post      Calls solve when done
         @return    A TwoSum instance
         */
        TwoSum(signed long long target, std::vector<signed long long> nums);
        
        /**
         @brief     Constructor for class, non-parameterized
         @post      Sets sumExists to false as it can't exist if nums empty, 
                    target is set to zero
         @return    A TwoSum instance
         */
        TwoSum();
        
        /**
         @brief     Adds any new nums to the nums vector
         @param     newNums: vector<signed long long>, new nums to add to nums
         @post      nums holds all new nums in newNums vector, solve called at
                    end of function
         */
        void addNums(std::vector<signed long long> newNums);
        
        /**
         @brief     Removes any new nums from the nums vector
         @param     newNums: vector<signed long long>, new nums to remove
         @post      nums has all new nums removed if they exist, solve called
                    at end of function
         */
        void removeNums(std::vector<signed long long> newNums);
        
        /**
         @brief     Removes all nums from nums vector
         @post      nums vector is empty, sets sumExists to false as it can't
                    exist if there are no nums
         */
        void clear();
        
        /**
         @brief     Changes target to the new target
         @param     newTarge: signed long long, new target
         @post      target's value is updated, solve called at end of function
         */        
        void changeTarget(signed long long newTarget);
        
        /**
         @brief     Returns nums
         @return    nums: vector<signed long long>, the private variable nums
         */
        inline std::vector<signed long long> getNums() const;
        
        /**
         @brief     Returns target
         @return    targe: signed long long, the private variable target
         */        
        inline signed long long getTarget() const;
        
        /**
         @brief     Returns sumExists
         @return    sumExists: bool, the private variable sumExists
         */        
        inline bool targetExists() const;
        
        /**
         @brief     Returns string represenation of class
         @return    string, converts ints and vector to strings to return
         */
        std::string toString() const;
};