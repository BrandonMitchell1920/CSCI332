---
Renderer: GitLab Markdown
Version: 20210317.01
Term: Spring 2021 - CSCI 332 Design and Analysis of Algorithms
---

| Huffman Image Codec &sect;&nbsp;2.5,&nbsp;5.0,&nbsp;7.3,&nbsp;9.4 | S21 CSCI 332 Design and Analysis of Algorithms|
| :--- | :--- |
| Assigned: **2021-03-19** | Due Date: See Parts | 
| Abstract: | Utilize hash tables and huffman trees to create a binary encoded form of ASCII images for storage and retrieval - or transmission over networks.|
| Objectives: | 1. Space v. Time Trade-off Hashing<br> 2. Huffman Trees<br> 3. Pairing Functions<br> 4. Working with C++ Binary Files<br> 5. C++ STL Containers and Algorithms <br> 6. Algorithm Analysis|
| Grading: 45 pts| A (&ge;41.85); A- (&ge;40.50); <br> B+ (&ge;39.15); B (&ge;37.35); B- (&ge;36.00) <br> C+ (&ge;34.65); C (&ge;32.85); C- (&ge;31.75) <br> D+ (&ge;30.15); D (&ge;28.35); D- (&ge;27) |
| Outcomes: | R2 (CS: 5-1, 1, 6; SE: 1, III-1-2-1) <br> R4 (CS: 5-1, 2, 5; SE: 1, III-1-2-1) <br> R6 (CS: 5-1, 2, 6; SE: 1, III-1-2-1) <br> (see syllabus for description of course outcomes)|

## Project Description:

You will be given a _secret_ ASCII image to be encoded and stored for later retrieval, where it will need to be decoded. Such encoders/decoders are known as `codecs`, which is what you will be creating. The objective is to encode the ASCII characters that comprise the image into a binary form, and then send two (2) files - one being the binary encoded image, and the second being the codeword dictionary that one must possess in order to decode the binary file. The first file you could send over insecure public networks, while the second you would need to make sure only the intended party receives. 

The primary algorithms to use for your codec are a hash table and a Huffman tree to create a 2-pass codec used to create the contents of both files. This project is not easy and will require careful design and time management to get all parts completed. In the end, when done correctly, you will end up with a binary file that, when decoded, produces the original image.

## Program Input: 

The input file is provided as the single command line argument to the `hcodec` program you will create. Your program will need to look at the data contained in the file and determine if the file is one of the following three (3) types of file:

1. ASCII image data to be _encoded_ - defined as every byte being a printable character with ASCII values in the set $`\{(32)_{A} .. (126)_{A}\} \cup \{(10)_{A}, (13)_{A}\}`$, representing a _line feed_ and _carriage return_ respectively, and where $`(x)_{A}`$ represents the ASCII character decimal value, $`x`$.

1. Binary data to be _decoded_ - generated from the encoding of the ASCII image data, with the following formatting: 

    The start of every binary encoded ASCII image data file will start with a `signature block` that is comprised of the first four (4) bytes (32-bits) in the file. The format of this block is as follows (in 32 bit layout):  
    > `31 - 28` | Major version number of the codec; range of values [0 - 15]  
      `27 - 20` | Minor version number of the codec; range of values [0 - 255]  
      `19 - 00` | Magic number; fixed value of `0xC0DEC`

    The `signature block` will be followed by a $`(29)_{A}`$ character indicating the _group separator_, followed by a 32-bit word called the `count`, followed by another $`(29)_{A}`$ character, followed by `count` number of 32-bit words, known as the $`\pi`$-group, followed by another $`(29)_{A}`$ character, then followed by `count` number of `codewords` from the computed `codeword dictionary`. 

    Schematically, this looks like:  
    > &lt;Signature Block&gt;&lt;GS&gt;&lt;count&gt;&lt;GS&gt;&lt;$`\pi`$-group&gt;&lt;GS&gt;&lt;codewords&gt;  
    
    or  

    > &lt;Major&gt;&lt;Minor&gt;&lt;Magic&gt;&lt;GS&gt;&lt;count&gt;&lt;GS&gt;&lt;$`W_{1}`$&gt;&lt;$`W_{2}`$&gt;$`\cdots`$&lt;$`W_{count}`$&gt;&lt;GS&gt;&lt;$`CW_{1}`$&gt;&lt;$`CW_{2}`$&gt;$`\dots`$&lt;$`CW_{count}`$&gt;

1. A file whose contents are different in format than the above two - in which case the file is rejected - not processed - the user is informed, and the program exits. 

**Note:** During decoding, the `signature block` of the file must be checked agaisnt the `codec` version implemented in your `hcodec` application. If the `signature blocks` do not agree, then you must output a message to the user indicating:

1. A Major or Minor version mismatch, stating the major and minor encoded version of the file provided on the command line, and the major and minor version provided by the `codec` implemented in the `hcodec` executable.   
1. And/or a Magic number mismatch, stating the magic number found in the file provided on the command line, and the magic number used by the `codec` implemented in the `hcodec` executable. 

### Sample Input Files

The project contains a folder named `images` within which you will find a series of test images described as follows:   
> `CSCI232.in` contains a series of twelve (12) unique characters to create a nice looking display of the CSCI232 course prefix and number.  
`calvin.in` contains a significantly larger number of unique characters arranged to create the iconic Calvin from the _Calvin and Hobbes_ comic strip.  
`eyes.in` contains a large number of unique characters arranged to provide a shading illusion of eyes.  
`ghostbusters.in` contains a large number of unique characters to show the _no ghosts_ symbol from the 1984 Ghostbusters movie.  
`stegasaurus.in` contains a modest number of unique characters to show an iconic dinosaur. 

The `CSCI232.in` should be your test data set since it has so few individual characters. The contents of that file are as follows: 


       ,ad8888ba,    ad88888ba     ,ad8888ba,   88   ad888888b,   ad888888b,   ad888888b,  
      d8"'    `"8b  d8"     "8b   d8"'    `"8b  88  d8"     "88  d8"     "88  d8"     "88  
     d8'            Y8,          d8'            88          a8P          a8P          a8P  
     88             `Y8aaaaa,    88             88       ,d8P"        aad8"        ,d8P"   
     88               `"""""8b,  88             88     a8P"           ""Y8,      a8P"      
     Y8,                    `8b  Y8,            88   a8P'                "8b   a8P'        
      Y8a.    .a8P  Y8a     a8P   Y8a.    .a8P  88  d8"          Y8,     a88  d8"          
       `"Y8888Y"'    "Y88888P"     `"Y8888Y"'   88  88888888888   "Y888888P'  88888888888  


Note there is a row of spaces above the first visible line of characters and following the last line of visible characters. Be careful to understand where spaces are placed in these ASCII files - it is not always obvious where they are located.

## Encoding an ASCII Image File

The algorithmic steps for encoding an ASCII image file are as follows: 

   1. Generate a filename `bname.bin`, where `bname` is the basename of the input file.  
      This file will store the binary encoded image data. 
   1. Generate a filename `bname.cwd`, where `bname` is the basename of the input file.  
      This file will store the codeword dictionary for the input file. 
   1. Compute the Huffman Tree for the input file and store the association of the symbols in the file with their corresponding codeword in the `bname.cwd` file. You are free to develop your own format for how the information is stored in the file, but the file must be a binary file. 
   1. Create a _hash table_ called $`\pi`$-map into which image data will be stored in $`\langle K_{i}, V_{i} \rangle`$ pairs. 
   1. Iterate over every symbol in the ASCII image file (including spaces - but ignoring newlines):  
      1. If a symbol from the file is not within the valid ASCII value ranges, reject the file, stop processing, and indicate the issue with a rational error message to the user. 
      1. Record the Row - the symbol's Y-value
      1. Record the Column - the symbol's X-value.
      1. Compute the $`\pi(x_{i},y_{i})`$ - the pairing function of $`\mathbb{N}^{2} \rightarrow \mathbb{N}`$, where $`x_{i}`$ is the column of the ASCII image symbol $`s_{i}`$, and $`y_{i}`$ is the row of the ASCII image symbol $`s_{i}`$. Use this computed value for the _key value pair_ of the $`\pi`$-map; 
      1. Use the codeword dictionary to lookup the codeword for the symbol, which will become the _value_ of the _key value pair_. 
      1. Therefore, $`\forall\ s_{i} \in Image\ | \ \pi\text{-map} \leftarrow \langle K{_i} = \pi(x_{i}, y_{i}), V_{i} = \text{cwd}[s_{i}]\ \rangle`$
   1. Create a binary file with the name `bname.bin` from above. 
      1. output the signature block as described above, followed by the _group separator_ symbol
      1. output the size of the key space for the $`\pi`$-map, followed by another _group separator_ symbol
      1. output each key in the key space of the $`\pi`$-map, followed by a _group separator_ symbol
      1. output each value in the $`\pi`$-map, associated with and ordered by the keys output from the key space  
         (suggestion: create a bitset of sufficient size that is a multiple of 8 bits greater than or equal to the size (in bits) of all the values in the $`\pi`$-map, and use this to output the values, once constructed)
   1. Update the user
      1. Output each codeword followed by it symbol and the number of occurrences on a separate line
      1. Inform the user of the files created and their filenames

## Decoding an ASCII Image File

The algorithmic steps for decoding binary file into its ASCII image is as follows: 

   1. Read the first 32-bits from the input file - the signature block - and decompose into the _Major_ and _Minor_ version numbers, as well as the _Magic_ number. If the signature block is not in agreement with the `codec` implemented, reject the file, stop processing, and indicate the issue with a rational error message to the user. 
   1. Process the _group separator_ symbol 
   1. Create the $`\pi`$-map _hash table_
   1. Read in the `count` from the file, and process the _group separator_ symbol
   1. Obtain the total number of bytes in the file  
      1. Seek ahead `count` number of words + the size of the _group separator_ in the file;  
         This will place the file's read_pointer to the first byte of the first codeword stored.
      1. Using the method `tellp()`, obtain the offset (in bytes)
      1. Seek ahead to the end of the file
      1. Using the method `tellp()`, obtain the offset (in bytes)
      1. Using the values returned by the two (2) calls to `tellp()`, compute the total number of bytes occupied by all of the codewords and create a `bitset` of this size - remember, bitsets are measured in bits, not bytes
   1. Seek back to the first byte of the first codeword and read in all of the codewords into the `bitset`
   1. Seek back to the first number in the $`\pi`$-group
   1. Open the `bname.cwd` and read the data into an appropriate data structure
   1. Scan - bit by bit - the data in the `bitset`:  
      1. Compare the consecutive bits scanned to the codewords in the codeword dictionary for a match, retrieving the corresponding symbol,  $`V_{i} \leftarrow s_{i}`$ 
      1. Read in the value from the `bname.bin` and store, $`K_{i} \leftarrow n_{i}`$
      1. Insert the _key value pair_ into the $`\pi`$-map  
         $`\pi\text{-map}\ \leftarrow \langle K_{i}, V_{i} \rangle`$
      1. decrement the `counter`
      1. verify that when all bits in the `bitset` have been processed, the `counter` should be $`0`$. 
   1. Create an appropriate data structure to hold the image data 
   1. Iterate over the key space of the $`\pi`$-map:  
      1. For each, $`K_{i}`$, generate $` (x_{i}, y_{i}) \leftarrow Z(K_{i})`$, where $`Z`$ is the _invertible_ form of $`\pi`$. 
      1. Insert $`V_{i}`$ at the location $`(x_{i}, y_{i})`$ within the image data structure
   1. Output the image data structure to the terminal

## Project Schedule

- Part-0 Encoding (Due: **2021-04-05**) (45 Pts) 
- Part-1 Decoding (Due: **2021-04-19**) (45 Pts)

## Specific Project Tasks:

The following tasks should be completed to obtain the maximum points available for this assignment.

1. Obtaining your project files  
   1. Perform the following tasks on the Department GitLab Server:  
      1. Login to the Department GitLab server [gitlab.cs.mtech.edu](https://gitlab.cs.mtech.edu) with your email address and your password. 
      1. Select the project `huffmanimage` from the offering of this course.
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

- Part-0: 

   1. Explore the provided code. There are a lot of code examples as well as a working codeword generator for you to explore and use as needed.
   1. Before you code anything, make sure you understand  
      1. Different data structures you want to use - make use of C++ STL containers and their algorithms
      1. The different algorithms you will use on these data structures. 
      1. Pairing functions and how they work. 
      1. C++ File I/O for binary files - the ability to move around in a binary file. 
      1. The fundamental difference between a codeword - of variable bit length - and the need to work with bytes for File I/O.

- Part-1: 

   1. Similar to Part-0, make sure you understand the different data structures you need. 
   1. Specifically, how best to represent the image data will become important  
      1. select a data structure poorly, and it will be a lot of work to convert the data retrieved and stored into the $`\pi`$-map into the ASCII image
      1. select well the data structure, and the task will become straight forward

## Project Grading (for each part): 

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
  
