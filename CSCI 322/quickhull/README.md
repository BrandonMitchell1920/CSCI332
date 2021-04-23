---
Renderer: GitLab Markdown
Version: 20210226.01
Term: Spring 2021 - CSCI332 Design and Analysis of Algorithms
---

| Computing a Convex Hull from a set of Points &sect;&nbsp;2.6,&nbsp;2.7,&nbsp;5.5  | S21 CSCI 332 Design and Analysis of Algorithms|
| :--- | :--- |
| Assigned: **2021-02-26** | Due Date: See Parts | 
| Abstract: | Design and Implement a Divide and Conquer strategy for computing the convex hull of a set of points in $`\Re^{2}`$|
| Objectives: | 1. Divide and Conquer Algorithm Strategy<br> 2. Quickhull Algorithm <br> 3. Empirical Analysis of Algorithms <br> 4. Relating Problem Instances through Minimal-Change Concept <br> 5. C++ STL Containers and Algorithms <br> 6. Algorithm Analysis|
| Grading: 45 pts| A (&ge;41.85); A- (&ge;40.50); <br> B+ (&ge;39.15); B (&ge;37.35); B- (&ge;36.00) <br> C+ (&ge;34.65); C (&ge;32.85); C- (&ge;31.75) <br> D+ (&ge;30.15); D (&ge;28.35); D- (&ge;27) |
| Outcomes: | R2 (CS: 5-1, 1, 6; SE: 1, III-1-2-1) <br> R4 (CS: 5-1, 2, 5; SE: 1, III-1-2-1) <br> R6 (CS: 5-1, 2, 6; SE: 1, III-1-2-1) <br> (see syllabus for description of course outcomes)|

## Project Description:

Given a set,$`S`$ of $`n`$ points in $`\Re^{2}`$, compute the convex hull of this set using an _divide and conquer_ algorithm technique. This will require expressing the solution to the instance $`n`$ of the problem in terms of solving some number of smaller instances of the problem. One such approach is described in your textbook in &sect;&nbsp;5.5 using the _Quickhull_ algorithm. 

The Quickhull algorithm finds _extreme_ points, $`P_{1}`$ and $`P_{n}`$ in $`S`$  by ordering the points in $`S`$ along their x-axis - these points being on the convex hull. The line segment $`\overrightarrow{P_{1}P_{n}}`$ formed from these extreme points then divides the original set of points, $`S`$ into one set $`S_{1}`$ that is on one side of the line, and a different set $`S_{2}`$ that lies on the other set of the line. In this way, the algorithm has divided the problem into these two new sets. With each of these sets, then, the problem changes, and the goal is to find a point in $`S_{1}`$ that is the farthest away from the line $`\overrightarrow{P_{1}P_{n}}`$ - this point being on the convex hull. This now creates four partitions of $`S_{1}`$, only two of which need be explored, the others are in the interior space of the convex hull and therefore need not be considered. The problem proceeds this in this manner, continuing to break up the space into spaces with fewer, and fewer points. The problem is symmetric, with the set of points $`S_{2}`$ being broken up into smaller sets of points in exactly the same manner. Once all extremes have been found and added to the set of points forming the convex hull, the algorithm stops and returns the set of points forming the convex hull. 

The challenge is to write (at least) two (2) classes, one that represents a point, $`P_{i}(x_{i},y_{i}) \in \Re^{2}`$, with various behaviors, such as computing its distance from a line given two points through which the line passes. The second class is one that represents the convex hull of a set of points. Your divide and conquer solution should take no more time than $`\Theta(n \log n)`$

In addition, there is an empirical analysis of the algorithm that will make use of visualizing the input and solution spaces (see &sect;&nbsp;2.6,&nbsp;2.7 in your textbook). This will require you to write a routine named `render` that will take the initial set of points, the number of points in that set, and a set of points that form the convex hull and display the points in a scatter plot in an x,y coordinate system just large enough to contains all the points. Points not on the convex hull should be represented differently than points on the convex hull. Your `render` routine should take no longer than $`\Theta(n^{2})`$ to complete.

## Problem Input: 

The `main.cpp` file and the `Makefile` of the project will, by default, generate a solution that uses the following points in $`S`$:

> ( 1,  6) ( 4, 15) ( 7,  7) (10, 13) (11,  6)  
  (11, 18) (11, 21) (12, 10) (15, 18) (16,  6)  
  (18,  3) (18, 12) (19, 15) (22, 19)

and will generate a solution from these points of: 

> (1, 6) (4, 15) (11, 21) (18, 3) (22, 19)

If you were to render these points using the character `+` to represent a point not on the convex hull and `o` to represent a point on the convex hull, you might generate an image similar to the one below: 

```
Points provided as follows: 
  (1, 6)  (4, 15)  (7, 7)  (10, 13)  (11, 6)  (11, 18)  (11, 21)  (12, 10)  (15, 18)  (16, 6)  (18, 3)  (18, 12)  (19, 15)  (22, 19)
The points forming the hull include:
  (1, 6)  (4, 15)  (11, 21)  (18, 3)  (22, 19)
22|                                                
21|                       o                        
20|                                                
19|                                             o  
18|                       +       +                
17|                                                
16|                                                
15|         o                             +        
14|                                                
13|                     +                          
12|                                     +          
11|                                                
10|                         +                      
09|                                                
08|                                                
07|               +                                
06|   o                   +         +              
05|                                                
04|                                                
03|                                     o          
02|                                                
01|                                                
00|                                                
  +------------------------------------------------
    0 1 2 3 4 5 6 7 8 9 1 1 1 1 1 1 1 1 1 1 2 2 2 2
                        0 1 2 3 4 5 6 7 8 9 0 1 2 3

```

If you look at the code in the `main.cpp` file you will see the following section of code: 

```
int main()
{
#ifdef USERANDOM
    // select a random seed for random number generator
    std::srand(time(NULL));

    // collection of points from which to
    // compute the hull using quickull
    Point<double> points[POINT_SZ];
    for (int ndx = 0; ndx < POINT_SZ; ndx++)
        points[ndx] = Point<double>(std::rand()%XEXTENT, std::rand()%YEXTENT);
#else
    // static test set of points
    Point<double> points[] = {
        {1,6}, {4,15}, {7,7}, {10,13}, {11, 6},
        {11,18}, {11,21}, {12,10}, {15,18}, {16,6},
        {18,3}, {18,12}, {19, 15}, {22, 19}
    };
#endif
```

This code will conditionally compile different lines of the `main.cpp` file depending on whether the manifest constant `USERANDOM` is defined. If it is defined, the code will select up to `POINT_SZ` points to add to $`S`$ of the form, $`P_{i}(x_{i} \le \text{XEXTENT}, y_{i} \le \text{YEXTENT})`$. This will provide a random set of points for you to test, through empirical analysis, how well your algorithm performs. 

To define the `USERANDOM`, execute the command make as follows: 

> `make clean`  
`make OPTIONS=-DUSERANDOM`

### Project Schedule

- Part-0: (Due: **2021-03-06**) Clone, build, execute the provided code. Study and understand the code. Provide the code that will render the set of points and have completed the header files for your project. Push this solution to GitLab by midnight of this date. 
- Part-1: (Due: **2021-03-15**) Completed project, pushed to GitLab by midnight of this date.

## Specific Project Tasks:

The following tasks should be completed to obtain the maximum points available for this assignment.

1. Obtaining your project files  
   1. Perform the following tasks on the Department GitLab Server:  
      1. Login to the Department GitLab server [gitlab.cs.mtech.edu](https://gitlab.cs.mtech.edu) with your email address and your password. 
      1. Select the project `quickhull` from the offering of this course.
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

- Part-0: Explore the provided code and the `Makefile` that is used to conditionally build the driver program `./main`. Executing the command,
   > `make`  

   will build the driver program using a single set of points with a known solution (shown above). You should be able to use this version to test your `render` routine and test your solution to computing the convex hull. If you execute the commands, 
   > `make clean`  
     `make OPTIONS=-DUSERANDOM`  

   The driver program will be built to generate some number of random points with random x and y coordinates. You may look at the top of the `main.cpp` file to change these maximum values, but these have been selected to allow for the rendered image to fit within a standard terminal window. 

   1. Review the code provided in the project. 
   1. Provide code for the `render()` routing to generate a scatter plot of the points, rendering a point that is not on the convex hull differently than a point that is on the convex hull. The render routine must also draw both an x and y axis with coordinate labels sufficient to be abel to understand the x and y coordinates of the points on the scatter plot. 
   1. Build the program by executing the `make` command and execute the program using `./main` and verify that the points are rendered correctly. 
   1. Capture the output in a text file (or image file) named, `stdRenderOut.{txt,png}` and place in the project folder.
   1. Clean the project files by executing `make clean`, and then build the random points version using `make OPTIONS=-DUSERANDOM` and then execute the program using `./main`. 
   1. Capture the output in a text file (or image file) named, `rndRenderOut.{txt,png}` and place in the project folder. For this rendered output, there should be no points on the convex hull since that part of the project has not been complete. 
   1. Ensure and justify through analysis, that your `render()` routing completes in $`\le \Theta(n^{2})`$ time. 
   1. Provide in your files in this part of the project completed `Point.h` and `Quickhull.h` files consistent with their design documented in the `design` folder. 

- Part-1: Implement a _divide and conquer_ solution to computing the convex hull consistent with the _quickhull_ algorithm explored in your textbook and in class lecture. 
   1. You will need the mathematical ideas documented in the `design` folder to:  
      1. Determine if a point is to the ''left'' or ''right'' of a given line in $`\Re^{2}`$.
      1. Compute the distance of a point from a line through which two other points pass. 
   1. Construct a quickhull implementation that divides and conquers by finding extreme points as documented above and used by the quickhull algorithm. These extreme points will form the convex hull and must be stored in some container. 
   1. You must use container classes from the C++ STL where possible, or justify why they were not used. 
   1. You must use smart pointers if you use pointer variables in your solution.
   1. Your solution should comply with the design documents provided in the `design` folder or justify why your solution varied from this design.
   1. Your algorithm must execute in $`\le \Theta(n \log n)`$ time and you must provide this through a reasoned analysis as we have done throughout the semester in class. 
   1. Please capture the execution of your solution on the standard set of points and store in a file named, `solStdOut.{txt,png}`.
   1. Please capture the execution of your solution on a random set of points and store in a file named, `solRndOut.{txt,png}`.
   1. In addition to the rendered scatter plot, your output must also include the set of points provided and the set of points that form the convex hull.

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
  
