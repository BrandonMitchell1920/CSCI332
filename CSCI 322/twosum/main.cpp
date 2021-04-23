/** TwoSum Problem using TUI 
 * 
 * CSCI 332 Design and Analysis of Algorithms
 * Driver for the TwoSum Problem
 * 
 * Phillip J. Curtiss, Associate Professor
 * pcurtiss@mtech.edu, 406-496-4807
 * Department of Computer Science, Montana Tech
 */

/*
 * Modified by:     Brandon Mitchell
 * Descirption:     Used the reference code to contruct a lovely TUI for the 
 *                  user!  I have made TUI's before, but it was all by hand and
 *                  not as robust or reusable.  Mine, however, did change the
 *                  color of your selection.  Fancy.
 *
 *                  User has option to add nums, remove nums, clear nums, 
 *                  change target, and print out the answer!  They can also end
 *                  the program, but that isn't fun.
 */

#include <cstdlib>      // For EXIT_SUCCESS
#include <iostream>     // For I/O
#include <sstream>      // For parsing

#include "Menu.h"       // For the TUI stuff
#include "TwoSum.h"     // My TwoSum class

int main()
{
    // Used to continue or stop the application, static for use in lambda 
    // function (though, a lambda capture by reference would also work?)
    static bool appContinue = true;
    
    // Create instance of TwoSum class
    TwoSum sum;

    // Represents an application menu
    tui::Menu appMenu;
    
    // Change the titles so it is unique!  Also, give helpful info.
    appMenu.SetTitle("TwoSum Problem Solver DX!");
    appMenu.SetSubTitle("Note: Nums empty and target zero on start");
    appMenu.SetPrompt("Your choice?");
    
    // Choice to add nums
    appMenu.Insert(std::make_shared<tui::MenuItem>('1', "1.", "Add Nums", 
        "Add nums to TwoSum Problem", 
        [& sum](std::shared_ptr<tui::MenuItem> mi) -> bool
        {
            std::cout << "Type out all nums you wish to add on one line with "
                         "spaces inbetween.\n";

            // For storing nums until they are added
            std::string temp;
            std::getline(std::cin, temp);
            std::vector<signed long long> tempVec;

            // Convert to String Stream for parsing
            std::stringstream line(temp); 
            
            // Note, nums added as vector so solve is only called once.  If I 
            // added each one individually, I would have to call solve each 
            // time which would be ineffiecient.  I hold them all until I know
            // there are no more.  The same is done for remove.
            while(std::getline(line, temp, ' ')) 
            { 
                tempVec.push_back(std::stol(temp)); 
            } 
            
            // Add to TwoSum object
            sum.addNums(tempVec);
            
            return true;
        }));

    // Remove option, pretty much add but calls different TwoSum function
    appMenu.Insert(std::make_shared<tui::MenuItem>('2', "2.", "Remove Nums", 
        "Remove nums from TwoSum Problem", 
        [& sum](std::shared_ptr<tui::MenuItem> mi) -> bool
        {
            std::cout << "Type out all nums you wish to remove on one line "
                         "with spaces inbetween.  Nums not in problem are "
                         "ignored.\nOnly first of duplicates removed with one "
                         "num ([2 3 2] - [2 7] = [3 2]).\n";
                         
            // For storing nums until they are removed
            std::string temp;
            std::getline(std::cin, temp);
            std::vector<signed long long> tempVec;

            // Convert to String Stream for parsing
            std::stringstream line(temp); 
            
            // Same reasoning as above
            while(std::getline(line, temp, ' ')) 
            { 
                tempVec.push_back(std::stol(temp)); 
            } 
            
            // Add to TwoSum object
            sum.removeNums(tempVec);
            
            return true;
        }));
    
    // Remove all nums to start fresh!
    appMenu.Insert(std::make_shared<tui::MenuItem>('3', "3.", "Clear Nums", 
        "Remove all nums from TwoSum Problem", 
        [& sum](std::shared_ptr<tui::MenuItem> mi) -> bool
        {
            std::cout << "All nums are gone!  Be sure to add new nums now!\n";

            // Remove all nums
            sum.clear();
            
            return true;
        }));

    // Change Target   
    appMenu.Insert(std::make_shared<tui::MenuItem>('4', "4.", "Change Target", 
        "Changes the sum we are looking for", 
        [& sum](std::shared_ptr<tui::MenuItem> mi) -> bool
        {
            std::cout << "Input a new target value for the Two Sum problem.\n";

            // Get input
            signed long long temp;
            std::cin >> temp;

            // Change the target
            sum.changeTarget(temp);
            
            return true;
        }));

    // Output of answer, I have a toString function, but I also have getters
    // for the values in case I wanted to reuse this code for something else
    appMenu.Insert(std::make_shared<tui::MenuItem>('5', "5.", "Print Problem", 
        "Prints nums, target, and answer", 
        [& sum](std::shared_ptr<tui::MenuItem> mi) -> bool
        {
            // Get string and output
            std::cout << sum.toString() << std::endl;
            
            return true;
        }));

    // Killer choice, ends our wonderful program!
    appMenu.Insert(std::make_shared<tui::MenuItem>('6', "6.", 
        "Terminate Application", "Terminate the application", 
        [](std::shared_ptr<tui::MenuItem> mi) -> bool 
        {
            // Kill application
            appContinue = false;
            std::cout << "Exiting application ... Come again soon!" 
                      << std::endl;
            
            return true;
        }));

    // Junk var just for geline catch below, prevents output doubling ... most
    // of the time :(
    std::string trash;
    
    // Application menu event loop 
    while (appContinue)
    {
        // Draw TUI and execute user choice
        appMenu.Prompt()->Invoke();
        std::cout << "\n<Enter to Continue>" << std::endl;
        
        // Needed to clean buffer, easiest way that doesn't mess everything up,
        // also pauses for user to read
        std::getline(std::cin, trash);
    }

    // Return success (0) to the caller
    return (EXIT_SUCCESS);
}