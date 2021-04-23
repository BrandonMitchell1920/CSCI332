/*
 * Name:    Brandon Mitchell
 * Description: The header for the Knapsack class.  Class represents an
 *              instance of the Knapsack problem.  It reads in data from a file
 *              and solves the problem.  Class makes use of the BRGC class to
 *              generate the powerset used.  Various functions allow the user
 *              to get information about the problem or update the problem.
 */

#pragma once

#include <vector>       // Store the weight/values
#include <string>       // For fileName and toString functions
#include <fstream>      // Reading in file
 
#include "BRGC.h"       // Code for powerset

class Knapsack
{
    private:
    
        // Represents an entry for the problem
        struct Entry
        {
            unsigned long long weight, value;
        };
        
        // Hold the filename in case user needs it, also use in menu
        std::string fileName;
        
        // Weight of Knapsack, the solution entries, and the value of the 
        // solution entries
        unsigned long long knapWeight, solutionWeight, solutionVal;

        // Store problem entries and solution entries
        std::vector<Entry> problemEntries, solutionEntries;
        
        // Keep track if the current problem has a solution
        bool solutionExists;
        
        // BRGC instance, store it so we can reuse the powerset if possible to
        // speed up calculations
        BRGC grayCode;
        
        /**
         @brief     Iterates through powerset, checking each set to see which 
                    one has the highest value while being under weight
         @post      solutionEntries, solutionWeight,  solutionTotalVal, and 
                    solutionExists will be modified
         */        
        void solve();
        
    public:
    
        /**
         @brief     Parameterized constuctor for Knapsack class
         @param     newFileName: std::string, name of file to open
         @post      Calls updateFileName which in turns calls solve, may result
                    in certian private members being modified
         @return    A Knapsack instance
         */
        Knapsack(std::string newFileName);
        
        /**
         @brief     Non-paramertizsed constructor for Knapsack class
         @post      Sets fileName to "NULL", solutionExists to false, weight to
                    zero
         @return    A Knapsack instance
         */
        Knapsack();
        
        /**
         @brief     Opens the file newFileName and reads in data if possible
         @param     newFileName: std::string, name of file to open
         @pre       newFileName needs to be a valid file
         @post      Clears problemEntries vector and fills it with file data, 
                    sets fileName equal to newFileName, and calls solve,
                    dependent on pre condition
         @return    bool, signals if file opening was successful and values 
                    were set
         */
        bool updateFileName(std::string newFileName);
        
        /**
         @brief     Sets knapWeight equal to newWeight
         @param     newWeight: unsigned long long, the new weight for the bag
         @pre       knapWeight has been changed, solve is called
         */
        void updateWeight(unsigned long long newWeight);
        
        /**
         @brief     Converts the problemEntries vector to a string with the
                    knapWeight included
         @return    std::string, the problemEntries and knapWeight convereted 
                    to a string
         */
        std::string toStringProblem() const;
        
         /**
         @brief     Converts the solutionEntries vector to a string with the
                    solutionWeight and solutionTotalVal included
         @return    std::string, the solutionEntries, solutionWeight, and 
                    solutionTotalVal convereted to a string
         */       
        std::string toStringSolution() const;
        
        /**
         @brief     Returns the private var fileName
         @return    std::string, the private var fileName
         */
        inline std::string getFileName() const {return fileName;}
        
        /**
         @brief     Returns the private var knapWeight
         @return    unsigned long long, the private var knapWeight
         */
        inline unsigned long long getWeight() const {return knapWeight;}
        
        /**
         @brief     Returns the private var problemEntries
         @return    std::vector<Entry>, the private var problemEntries
         */
        inline std::vector<Entry> getProblemEntries() const 
		{
			return problemEntries;
		}
        
        /**
         @brief     Returns the private var solutionEntries
         @return    std::vector<Entry>, the private var solutionEntries
         */        
        inline std::vector<Entry> getSolutionEntries() const
		{
			return solutionEntries;
		}

        /**
         @brief     Returns the private var solutionExists
         @return    bool, the private var solutionExists
         */        
		inline bool doesSolutionExist() const {return solutionExists;}
};