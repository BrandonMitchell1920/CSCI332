/**
 * Compute the Binary Reflected Gray Codes for a given positive integer n provided on the command line
 * using the minimal-change decrease-and-conquer by a constant approach 
 *
 * Phillip J. Curtiss, Associate Professor
 * pcurtiss@mtech.edu, 406-496-4807
 * Department of Computer Science, Montana Tech
 */

/*
 * Modified by: Brandon Mitchell
 * Description: Uses the TUI menu to create an interative menu for managing the
 *              Knapsack class.  Users can read in files, change the weight,
 *              print out info about the problem, and print out info about the
 *              solution.
 */

#include <cstdlib>      // Standard C++ library prototypes
#include <iostream>     // Input/output stream prototypes
#include <string>       // Required for string to numeric 

#include "Menu.h"       // Menu and MenuItem classes
#include "BRGC.h"       // Powerset of n-items using Binary Reflected Gray Code

#include "Knapsack.h"   // Knapsack class, solves Knapsack problem

int main()
{
	// Used to continue or stop the application
	bool appContinue = true;

	// Represents the application menu, set values
	tui::Menu appMenu;
	appMenu.SetTitle("Knapsack Problem Solver DX!!!");
    appMenu.SetPrompt("Your choice?");
    
    // Instance of the Knapsack problem
    Knapsack bag;

	// Menu choice for updating the filename
	appMenu.Insert(std::make_shared<tui::MenuItem>('1', "1.", "Update File",
		"Reads in Knapsack data from a file", 
		[& bag](std::shared_ptr<tui::MenuItem> mi) -> bool
		{
			// Query user and store file name for later
			std::string newFile;
			std::cout << "Please give the name of a file containing Knapsack "
						 "problem data.\n";
			std::getline(std::cin, newFile);
			
			// Check return value to make sure it was updated successfully
			if (!bag.updateFileName(newFile))
			{
				std::cout << "Sorry, that file doesn't exist.  Return to "
							 "menu and give a different file name.\n";
			}	
			
			return true;
		}));

	// Menu choice for changing the bag's weight
	appMenu.Insert(std::make_shared<tui::MenuItem>('2', "2.", "Update Weight",
		"Changes the total weight of the Knapsack", 
		[& bag](std::shared_ptr<tui::MenuItem> mi) -> bool
		{
			// Query the user for the weight
			unsigned long long newWeight;
			std::cout << "Please give an unsigned value for the weight of "
					     "the Knapsack.\n";
			std::cin >> newWeight;
			
			// Give the bag the new weight
			bag.updateWeight(newWeight);
			
			return true;
		}));

	// Menu choice for viewing the current problem values
	appMenu.Insert(std::make_shared<tui::MenuItem>('3', "3.", "View Problem",
		"Prints out the problem values of the Knapsack problem", 
		[& bag](std::shared_ptr<tui::MenuItem> mi) -> bool
		{
			// Call toString function and ouptut it
			std::cout << bag.toStringProblem();
			
			return true;
		}));
		
	// Menu choice for viewing the current solution values
	appMenu.Insert(std::make_shared<tui::MenuItem>('4', "4.", "View Solution",
		"Prints out the solution values of the Knapsack problem", 
		[& bag](std::shared_ptr<tui::MenuItem> mi) -> bool
		{
			// Call toString function and ouptut it, note, a different one 
			// from above
			std::cout << bag.toStringSolution();
			
			return true;
		}));	

	// Add menu item for Exit
	appMenu.Insert(std::make_shared<tui::MenuItem>('5', "5.", "End Program", 
		"Kills the application", 
		[& appContinue](std::shared_ptr<tui::MenuItem> mi) -> bool
		{
			// Set loop var to false and inform user
			appContinue = false;
			std::cout << "Exiting application... Come again soon!\n";
			
			return true;
		}));

    // For getline catch below
    std::string trash;

	// Change subtitle to update useful information
	appMenu.SetSubTitle("Current file: " + bag.getFileName() + " | Current "
		"weight: " + std::to_string(bag.getWeight()) + " | Solution "
		"exists: " + (bag.doesSolutionExist() ?  "Yes" : "No"));

	// Application menu event loop
	while (appContinue)
	{
		// prompt the user and invoke the selected menu item
		appMenu.Prompt()->Invoke();
		
		std::cout << "<Enter to Continue>" << std::endl;
		
		// Attempt to clear cin buffer
		std::getline(std::cin, trash);
		
		// Update after user has made a choice
		appMenu.SetSubTitle("Current file: " + bag.getFileName() + " | Current "
			"weight: " + std::to_string(bag.getWeight()) + " | Solution "
			"exists: " + (bag.doesSolutionExist() ?  "Yes" : "No"));
	}
	
	// Return indicating success
	return(EXIT_SUCCESS);
}