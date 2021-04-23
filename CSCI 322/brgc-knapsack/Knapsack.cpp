/*
 * Name:    Brandon Mitchell
 * Description: The implentation of the Knapsack class.  I inlined a few 
 *              functions, and the compiler complained about them, so they are
 *              defined in the header.
 */

#include "Knapsack.h"

// Private solve method, only called when weight or file changed
void Knapsack::solve()
{
    // Get list of strings from BRGC, simply get the L pointer, only caluculate
    // if the problemEntries vector has changed size
    auto list = grayCode.getPowerSet();
    
    // Set up temp values to hold the set, maxes
    std::vector<Knapsack::Entry> temp;
    unsigned long long tempWeight, tempValue;
    
    // Clear answer vector, set equal to temp vector in loop
	solutionWeight = solutionVal = 0;
    solutionEntries.clear();
    solutionExists = false;
    
    // Walk through list, looking at each string
    for (auto str : (* list))
    {
        // Reset values
        temp.clear();
		tempWeight = tempValue = 0;
		
		// No way the user can possibly have enough values to overflow, a power
        // set over 255 would never finish before this can run!
        for (unsigned char i = 0; i < str.length(); i++)
		{
            // Could also check if equal to 0, get same answer
			if (str[i] == '1')
			{
                // Add value to temp vec and add weight and value to temp vals
				temp.push_back(problemEntries[i]);
				tempWeight += problemEntries[i].weight;
				tempValue += problemEntries[i].value;
			}
		}
		
        // Weight has to be <= the bag's weight and greater than the current
        // solution's value, note first solution with highest val saved, if two
        // solutions have the same value, the first found is kept
		if (tempWeight <= knapWeight && tempValue > solutionVal)
		{
            // Save values for later and next iteration, set bool
			solutionEntries = temp;
			solutionWeight = tempWeight;
			solutionVal = tempValue;
            solutionExists = true;
		}
    }
}

// Parameterized constructor, updates file name which then calls solve
Knapsack::Knapsack(std::string newFileName)
{
    Knapsack::updateFileName(newFileName);
}

// Non-parameterized constructor, sets default values
Knapsack::Knapsack() : fileName("NULL"), solutionExists(false) {}

// Reads in the data, and then calls solve
bool Knapsack::updateFileName(std::string newFileName)
{
    // Filestream object
    std::ifstream inFile(newFileName);
    
    // If it doesn't exists, return false
    if (inFile.is_open())
    {
        // Save filename, user may want it, perhaps they forgot what file they
        // opened?
        fileName = newFileName;
        
        // Values for entries
        unsigned long long itemWeight, itemValue, numItems;

        // First line of file is the weight of bag and number of entries
        inFile >> knapWeight >> numItems;
        
        // If the number of problems has changed, the powerset needs to be 
        // updated
        if (numItems != problemEntries.size()) 
        {
            grayCode.calcPowerSet(numItems);
        }
        
        // Clear all problem entries
        problemEntries.clear();
        
        // Add each entry to vector
        while (inFile >> itemWeight >> itemValue)
        {
            problemEntries.push_back(Knapsack::Entry{itemWeight, itemValue});
        }
        
        // Calls private solve method, store answer in answer vector
        solve();
        
        return true;
    }
    
    // Check return value in main, originally had an exception, but that was
    // not needed as I could just have it return true or false
    else
    {
        return false;
    }
}

// Changes knapWeight and then calls solve
void Knapsack::updateWeight(unsigned long long newWeight)
{
    // Update weight, have to call solve as current solution likely isn't 
    // viable anymore
    knapWeight = newWeight;
    solve();
}

// Returns the problem entries as a string with extra information for user
std::string Knapsack::toStringProblem() const
{
	// Output the weight of Knapsack to user and the different values in the 
	// problem
    std::string str = "Knapsack Weight: \t" + std::to_string(knapWeight) +
					  "\nItems in problem:\nWeight\tValue\n";
					  
    // Loop through solution vector, add each to str
	for (auto var : problemEntries)
	{
		str += std::to_string(var.weight) + "\t" + std::to_string(var.value) + 
			   "\n";
	}
	
	return str;
}

// Returns the solution entries as a string with extra information for user
std::string Knapsack::toStringSolution() const
{
	// Total weight, value, and message to user
    std::string str = "Total Weight: \t" + std::to_string(solutionWeight) + "\n"
	                  "Total Value: \t" + std::to_string(solutionVal) + "\n"
					  "Items in solution:\nWeight\tValue\n";
					
	// Loop through solution values, add each to str
	for (auto var : solutionEntries)
	{
		str += std::to_string(var.weight) + "\t" + std::to_string(var.value) + 
			   "\n"; 
	}
	
	return str;
}