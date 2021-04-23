---
Renderer: GitLab Markdown
Version: 20210129.01
Term: Spring 2021 - CSCI332 Design and Analysis of Algorithms
---

| Binary Reflected Gray Code | S21 CSCI 332 Design and Analysis of Algorithms  |
| :--- | :--- |
| Assigned: **2021-02-08** | Due Date: **2021-02-22** | 
| Abstract: | Explore the use of a recursive implementation of BRGC and make use of it to solve instances of the Knapsack Problem by Exhaustive Search|
| Objectives: | 1. Decrease and Conquer by a Constant<br> 2. Binary Reflected Gray Code Algorithm <br> 3. Knapsack Exhaustive Search Algorithm <br> 4. Relating Problem Instances through Minimal-Change Concept <br> 5. C++ STL Containers and Algorithms <br> 6. Algorithm Analysis|
| Grading: 45 pts| A (&ge;41.85); A- (&ge;40.50); <br> B+ (&ge;39.15); B (&ge;37.35); B- (&ge;36.00) <br> C+ (&ge;34.65); C (&ge;32.85); C- (&ge;31.75) <br> D+ (&ge;30.15); D (&ge;28.35); D- (&ge;27) |
| Outcomes: | R2 (CS: 5-1, 1, 6; SE: 1, III-1-2-1) <br> R4 (CS: 5-1, 2, 5; SE: 1, III-1-2-1) <br> R6 (CS: 5-1, 2, 6; SE: 1, III-1-2-1) <br> (see syllabus for description of course outcomes)|

## Project Description:

Solving instances of the `Knapsack` problem using _exhaustive search_ brute force techniques requires the generation of the power set of the candidate items to be placed into the knapsack of size $`W`$. The efficiency of an exhaustive search solution to this problem depends, therefore, on finding an efficient means of generating the elements of the power set of items. 

You are provided an implementation of a `Binary Reflected Gray Code (BRGC)` recursive algorithm that makes use do the _minimal change_ approach to achieve a decrease-and-conquer by a constant factor efficiency. You are to make use of this code in your solution as you design and implement the exhaustive search algorithm for the Knapsack problem. 

You are also provided the _textual user interface_ library from the first project to use to interact with the user and present the results. 

## Problem Input: 

Instances of the problem will be provided in test files which have the form: 

> 10 4  
  3 2  
  1 6  
  4 22  
  2 11

Where the first line contains the size (weight) of the knapsack, $`W`$, and the number, $`n`$, of candidate items that can be selected to be placed inside the knapsack; the example being knapsack size of 10, and 4 candidate items. The next $`n`$ lines of the input describe each item's weight (the first number) and its value (the second number). 

You must prompt the user for the input file name, initialize an instance of the Knapsack problem, and then allow the user to obtain the solution, which should include: 

> 1. The sum of the size of all the items selected to go inside the knapsack  
> 1. The sum of the value of all the items selected to go inside the knapsack
> 1. A list of the items selected to go inside the knapsack, showing for each item,  
>    1. Its weight 
>    1. Its value

If there is no solution to the problem, state so upon request for a solution to the instance. 

## Specific Project Tasks:

The following tasks should be completed to obtain the maximum points available for this assignment.

1. Obtaining your project files  
   1. Perform the following tasks on the Department GitLab Server:  
      1. Login to the Department GitLab server [gitlab.cs.mtech.edu](https://gitlab.cs.mtech.edu) with your email address and your password. 
      1. Select the project `BRGC-Knapsack` from the offering of this course.
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
1. Run the executable by typing `./driver` at the command prompt and select `b` from the menu. Enter a valid value and observe the output. 
1. Make sure you understand the code in the `BRGC class`. 
1. Create a new class `Knapsack` that implements the exhaustive search solution of the Knapsack problem. 
1. Your class needs to expose methods that allow the user to:
   1. provide the name of the input file to use for an instance of the problem.
   1. find the solution to the problem instance
   1. interactively change the size of the Knapsack - after loading the instance from the file. 
   1. display the current instance of the problem; including the size of the knapsack, and each item showing its weight and value
1. Your solution must also make use of the _textural user interface_ library provided under the subfolder `menu`. 
1. You have been provided a driver program in `main.cpp` that should be updated to instantiate your `Knapsack` class and create the needed menu items on the application menu to invoke the behaviors required to complete the project. 
1. You should also include a UML class diagram of your solution, showing all class relationships to other classes including the STL - no need to provide data or method sections for class diagrams from the STL library.
1. You must include a file `analysis.pdf` in your project that provides a sketch of how to analyze this problem, including the `BRGC`
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


  
