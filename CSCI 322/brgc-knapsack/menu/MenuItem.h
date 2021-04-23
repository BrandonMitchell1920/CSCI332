/** Application Menu via Textual User Interface
 * 
 * CSCI 332 Design and Analysis of Algorithms
 * MenuItem Class
 * 
 * Phillip J. Curtiss, Associate Professor
 * pcurtiss@mtech.edu, 406-496-4807
 * Department of Computer Science, Montana Tech
 */
#ifndef MENUITEM_H
#define MENUITEM_H

#include <string>
#include <memory>
#include <functional>

namespace tui {

  class MenuItem : public std::enable_shared_from_this<MenuItem> {
    private:
      // keyboard character used by user to select
      char cmd;

      // name displayed on application menu
      std::string name;

      // description displayed on application menu
      std::string description;

      // help informaiton displayed on application menu
      // at row designated by Menu instance
      std::string help;

      // an instance of function<T> refering to a method that
      // is executed by the Invoke() method
      std::function<bool(std::shared_ptr<MenuItem>)> behavior;

    public:
      // Constructor to make a MenuItem instance
      MenuItem(char cmd,
               std::string name,
               std::string description,
               std::string help,
               std::function<bool(std::shared_ptr<MenuItem>)> behavior);

      // render the MenuItem onto the application menu
      void DisplayItem() const;

      // render the additional help information about the highlighted
      // MenuItem
      void DisplayHelp() const;

      // return the keyboard character used to select this MenuItem
      char GetCmd() const;

      // execute the method reference by behavior
      bool Invoke();
  }; // end MenuItem

} // end namespace

#endif