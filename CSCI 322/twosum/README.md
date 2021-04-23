---
Renderer: GitLab Markdown
Version: 20210120.01
Term: Spring 2021 - CSCI332 Design and Analysis of Algorithms
---

| Two-Sum Problem | S21 CSCI 332 Design and Analysis of Algorithms  |
| :--- | :--- |
| Assigned: **2021-01-20** | Due Date: **2021-02-01** | 
| Abstract: | Design and implement a class to solve the Two-Sum problem |
| Objectives: | 1. C Language Pointers<br> 2. Using Custom Libraries <br> 3. Writing C++ Classes <br> 4. Brute Force Algorithm|
| Grading: 45 pts| A (&ge;41.85); A- (&ge;41.85); <br> B+ (&ge;39.15); B (&ge;37.35); B- (&ge;36.00) <br> C+ (&ge;34.65); C (&ge;32.85); C- (&ge;31.75) <br> D+ (&ge;30.15); D (&ge;28.35); D- (&ge;27) |
| Outcomes: | R2 (CS: 5-1, 1, 6; SE: 1, III-1-2-1) <br> R4 (CS: 5-1, 2, 5; SE: 1, III-1-2-1) <br> R6 (CS: 5-1, 2, 6; SE: 1, III-1-2-1) <br> (see syllabus for description of course outcomes)|

## Project Description:

You must create a class called `TwoSum` that uses an STL container class to hold a list of integers, `L` and a target value `k`. The class will implement an algorithm that will return a boolean value of `true` if there exists a pair of elements `(a,b)` where `a` is in `L` and `b` is in `L` and `a + b = k`, and `false` otherwise. 

You will make use of the _textual user interface_ (TUI) to interact with the user to obtain `L`, `k`, and perform all operations from the `TwoSum` class. 

## Specific Project Tasks:

The following tasks should be completed to obtain the maximum points available for this assignment.

1. Obtaining your project files  
   1. Perform the following tasks on the Department GitLab Server:  
      1. Login to the Department GitLab server [gitlab.cs.mtech.edu](https://gitlab.cs.mtech.edu) with your email address and your password. 
      1. Select the project `TwoSum` from the offering of this course.
      1. Click on the **fork** button to create a copy of this project under your own GitLab account.
      1. Go to the **project settings** menu and then the **members** option and add your instructor and any teaching assistants as developers to your copy of the project. 
      1. Lastly, go back to this project under your account and click the icon to the right of the project URL. This will copy the project URL to the clipboard so you may paste it in the next sequence of steps. 
   1. Perform the following tasks on the Department Linux server `lumen.cs.mtech.edu`. 
      1. Login to the Department's Linux server with your credentials. 
      1. Execute the commands 
      ```
      mkdir -p ~/CSCI332/Projects
      cd ~/CSCI332/Projects
      ```
      3. Execute the command `git clone <url>`, where `<url>` is pasted from the clipboard.
      1. Change into the directory created by the `git clone` command to perform the rest of the tasks for this project. 
1. Review the code provided in the project. 
1. You need to create a C++ class `TwoSum` that makes use of one of the STL container classes to hold a list of integers and also holds the target sum. 
1. Your class needs to expose methods that allow:
   1. The user to manage the integer values in the list of integers
   1. The user to manage the target sum
   1. Provides the answer to the `TwoSum` problem by returning a `Yes` or `No` answer. 
1. Output should include the value of the list of integers, the value of the target sum, and the `Yes` or `No` answer to the `TwoSum` question.
1. Your application must also make use of the _textural user interface_ that is provided under the subfolder `menu`. 
   1. You should review this code and complete any code that is incomplete. 
1. You have been provided a driver program in `main.cpp` that should be updated to instantiate your `TwoSum` class and create the needed menu items on the application menu to invoke the behaviors required to complete the project. 
1. You should also include a UML class diagram of your `TwoSum` class, showing any class relationships to other classes including the STL - no need to provide data or method sections for class diagrams from the STL library.
1. You must include a file `analysis.pdf` in your project that shows the formal analysis of your algorithmic solution to the `TwoSum` problem. 
   1. If your solution is not a brute force algorithm, describe why it fails the definition of a brute force algorithm, and 
   1. Contrast how your formal analysis of your solution with that of the brute force algorithmic solution.
1. Your program should compile and operate without warnings or errors. 
1. When your solution is complete, please `push` back to the GitLab server your code with a final commit message of `Please Grade`.

## Project Grading: 

The project must compile without error (ideally without warnings) and should not fault upon execution. All exceptions should be caught if thrown and handled in a rational manner. Grading will follow the *project grading rubric* shown below: 

| Attribute (Pts) | Exceptional (1) | Acceptable (0.8) | Amateur (0.7) | Unsatisfactory (0.6) | 
| :---:           | :---            | :---             | :---          | :---                 |
| Specification (10) | The program works and meets all of the specifications. | The program works and produces correct results and displays them correctly. It also meets most of the other specifications. | The program produces correct results, but does not display them correctly. | The program produces incorrect results. |
| Readability (10) | The code is exceptionally well organized and very easy to follow. | The code is fairly easy to read. | The code is readable only by someone who knows what it is supposed to be doing. | The code is poorly organized and very difficult to read. | 
| Reusability (10) | The code only could be reused as a whole or each routine could be reused. | Most of the code could be reused in other programs. | Some parts of the code could be reused in other programs. | The code is not organized for reusability. | 
| Documentation (10) | The documentation is well written and clearly explains what the code is accomplishing and how. | The documentation consists of embedded comments and some simple header documentation that is somewhat useful in understanding the code. | The documentation is simply comments embedded in the code with some simple header comments separating routines. | The documentation is simply comments embedded in the code and does not help the reader understand the code. | 
| Efficiency (5) | The code is extremely efficient without sacrificing readability and understanding. | The code is fairly efficient without sacrificing readability and understanding. | The code is brute force and unnecessarily long. | The cod eis huge and appears to be patched together. | 
| Delivery (total) | The program was delivered on-time. | The program was delivered within a week of the due date | The program was delivered within 2-weeks of the due date. | The code was more than 2-weeks overdue. | 

### Example: 

The *delivery* attribute weights will be applied to the total score from the other attributes. If a project scores 36 points total for the sum of *specification*, *readability*, *reusability*, *documentation*, and *efficiency* attributes, but was turned in within 2-weeks after the due date, the project score would be $`36\cdot 0.7 = 25.2`$. 

## Collaboration Opportunities: 

This project provides *no collaboration opportunities* for the students. Students are expected to design and implement an original solution specific in this project description. Any work used that is not original should be cited and properly references in both the code and in any accompanying write-up. Failure to cite code that is not original may lead to claims of academic dishonesty against the student - if in doubt of when to cite, see your instructor for clarification. 


  
