/*
 * Name:    Brandon Mitchell
 * Description: Implentation of TwoSum class.  Stores nums, a target, and can
 *              calculate the two sum problem.  The user can then access the 
 *              SumExists variable to see what the result is.
 */

#include "TwoSum.h"

// Checks the vector for any TwoSum nums
void TwoSum::solve()
{
    // Store numbers in map, has constant access time, doesn't matter if 
    // multiple same numbers are in nums vector, note value is bool, doesn't 
    // matter, only need placeholder for value, only checking if key exists
    std::unordered_map<signed long long, bool> map;
   
    for (signed long long num : nums)
    {        
        // target - num is the number that matches the current num, if it is in
        // the map, then we have two nums that equal the target, find is 
        // constant, so it is used to see if key exists
        if (map.find(target - num) != map.end())
        {
            sumExists = true;
            
            // Return early as we only need to see if one couple of nums add to
            // the sum
            return;
        }
        
        // Not in map?  Add to map.
        else
        {
            map.insert({num, false});
        }
    }
    
    sumExists = false;
}

// Constructor for class
TwoSum::TwoSum(signed long long target, std::vector<signed long long> nums) :
    target(target), nums(nums) 
{
    // Calculate
    solve();
}

// Non-parameterized constructor
TwoSum::TwoSum() : target(0), nums({})
{
    // Set to false as we don't need to do a caluculation to find answer
    sumExists = false;
}

// Add the nums to the nums vector, note, it takes a vector so multiple nums 
// can be added at once before solve is called, if ten nums were added
// individually, we would be wasting resources, user may want to add many at a 
// time, or just one
void TwoSum::addNums(std::vector<signed long long> newNums)
{
    // Add each num in vector to nums vector
    nums.insert(nums.end(), newNums.begin(), newNums.end());
    
    // Recalculate    
    solve();
}

// Removes nums from the nums vector, same thing as above
void TwoSum::removeNums(std::vector<signed long long> newNums)
{
    for (signed long long num : newNums)
    {
        // If the num is in the nums vector, remove it
        auto it = find(nums.begin(), nums.end(), num);
        if (it != nums.end()) {nums.erase(it);}
    }
    
    // Recalculate    
    solve();
}

// Removes all nums from vector
void TwoSum::clear() 
{
    // Remove all nums
    nums.clear(); 
    
    // Set to false as it can't be true, no point to call solve
    sumExists = false;
}

// Change the target value
void TwoSum::changeTarget(signed long long newTarget)
{
    // Update sum
    target = newTarget;
    
    // Recalculate
    solve();
}

// Returns the sumExists variable
inline bool TwoSum::targetExists() const {return sumExists;}

// Returns the target value
inline signed long long TwoSum::getTarget() const {return target;}

// Returns the nums vector
inline std::vector<signed long long> TwoSum::getNums() const {return nums;}

// Returns a string represenation of the class
std::string TwoSum::toString() const
{
    // Variable to return
    std::string str = "Nums:\t\t[";
    
    // Add each number nicely formatted
    for (signed long long num : nums)
    {
        str += " " + std::to_string(num) + ",";
    }
    
    // Remove extra comma if necessary
    if (str.back() == ',') {str.pop_back();}
    
    // Close off vector of nums
    str += " ]\n";
    
    // Add on the target and some words
    str += "Target:\t\t" + std::to_string(target) + "\nSum Exists:\t";
    
    // Add on the sumExists variable all colorful!
    str += (sumExists ? "\x1b[42mYes\x1b[0m" : "\x1b[41mNo\x1b[0m");
    
    return str;
}