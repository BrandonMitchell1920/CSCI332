/** Application Menu via Textual User Interface
 * 
 * CSCI 332 Design and Analysis of Algorithms
 * Menu Class
 * 
 * Phillip J. Curtiss, Associate Professor
 * pcurtiss@mtech.edu, 406-496-4807
 * Department of Computer Science, Montana Tech
 */
#ifndef MENU_H
#define MENU_H

#include <string>
#include <vector>
#include <memory>

#include "MenuItem.h"

namespace tui {

  class Menu {
    private:
      // title of the application menu
      std::string title;

      // subtitle of the application menu
      std::string subTitle;

      // prompt for the application menu
      std::string prompt;

      // virtual terminal row where 
      // the application menu will begin 
      int startLine;

      // virtual terminal row where 
      // additional help information about a menu 
      // item will be displayed 
      int helpLine;

      // virtual terminal column where
      // the menu item will begin to be displayed
      int leftMargin;
      std::vector<std::shared_ptr<MenuItem> > Items;

      // function to exit the textual users interface
      // cleanly and restore terminal functionality
      static void exitCurses(int signal);

    public:
      // constructor
      Menu();

      // destructor
      ~Menu();

      // methods to modify the Items collection with MenuItem instances
      std::shared_ptr<MenuItem> Insert(std::shared_ptr<MenuItem> Item);
      std::shared_ptr<MenuItem> Update(char cmd, std::shared_ptr<MenuItem> Item);
      std::shared_ptr<MenuItem> Remove(char cmd);

      // Display the application menu and obtain a valid input from the user
      // return the menu item instance corresponding with the menu item selected
      std::shared_ptr<MenuItem> Prompt() const;

      // mutator methods for the virtual terminal window parameters
      void SetTitle(std::string msg);
      void SetSubTitle(std::string msg);
      void SetPrompt(std::string msg);
  }; // end Menu

} // end namespace

#endif