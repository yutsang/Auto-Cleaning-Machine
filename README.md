# PA2-Auto-Cleaning-Machine  
## 1. Introduction

You are going to write the internal brain (functions) for an auto cleaning robot. You will need to think about how the robot interprets a given map, considers the constraints from the actual environment and designs an optimal
path and solutions.  
<img width="861" alt="Screenshot 2022-10-02 at 11 58 15" src="https://user-images.githubusercontent.com/19373417/193437194-32c0802c-d647-4478-9052-133713923c4d.png">

## 2. Important requirements
To make the assignment a good practice of writing proper recursions, you will get zero mark if you do not follow any of the following rules.

* You are NOT allowed to use any kind of loops in any part of your submitted code, except for the given function.
* You are NOT allowed to change our given functions.
* To be precise: All given functions are in given_function.cpp; your pa2.cpp should NOT have any loops. (Updated: Oct 31 5:50pm)
* You are NOT allowed to use goto.
* You are NOT allowed to use any global variable, or static variable like static int x.
* You are NOT allowed to include any additional libraries yourself. Everything you need is already included. Especially, you can only use cstring library, and you cannot use C++ string library.
* You are NOT allowed to modify any of the given function prototypes including the return types, function names, default values, and parameter lists.

## 3. Overview
### 3.1 Map
We use a text file map.txt to store the initial map we use in the program. We will change this and test with different maps (may also be in different sizes) when we grade your assignment.  
Here is a map given in the file, map.txt:  
<img width="108" alt="Screenshot 2022-10-02 at 11 58 48" src="https://user-images.githubusercontent.com/19373417/193437204-178e6181-3dc0-44d4-a18d-2c8447eb81c6.png">  
The symbol B means a blocked area, the symbol C means the charger and the empty
space (' ') means the available space that the robot can move.  
We will load the map from map.txt to our program by the given function loadMap:  
<img width="182" alt="Screenshot 2022-10-02 at 12 13 42" src="https://user-images.githubusercontent.com/19373417/193437509-fd958031-6e92-4f32-96c5-d81af8831922.png">  
Then this map is stored in and can be retrieved by this 2D char array:  
<img width="214" alt="Screenshot 2022-10-02 at 12 14 04" src="https://user-images.githubusercontent.com/19373417/193437518-a2fca24b-d1ec-4e17-b629-f457bee3d95d.png">  
This map is copied to another 2D char array, result_map. It will be passed and may be modified by one of the TODO function:  
<img width="263" alt="Screenshot 2022-10-02 at 12 14 38" src="https://user-images.githubusercontent.com/19373417/193437535-f05dbdc9-1606-427c-87f7-0a36c6ef642d.png">  
In our assignment, the world is in 2D. After setting the position of the robot (symbol R, if we print the above 2D arrays using the given function printMap (which will be discussed in Given Functions), the output will be shown as follows:  
<img width="100" alt="Screenshot 2022-10-02 at 12 15 16" src="https://user-images.githubusercontent.com/19373417/193437554-b956a449-e004-455e-a7bd-cb07f485b6bc.png">  
The world above is with size 12 by 12 (i.e. 12 rows and 12 columns). The type of a particular position can be accessed by map[y][x], where y is the row index and x is the column index. For example, map[6][2] corresponds to the position (2, 6) and is the symbol 'C'.  
It is important to note that, in C++ programs, it is common for programmers to use the first dimension of a 2D array as the row index while the second dimension is used as the column index, due to how the 2D array is actually stored in the memory. Therefore, if the world above is stored in a 2D array map, then the position at (x, y) is actually represented by map[y][x].  
Every position in the map will be in one of the following types:  
* The available area is denoted by ' '(empty). It is the place that the robot can move to.  
* The blocked area is denoted by 'B'. It is the place that the robot cannot move to.
* The robot is denoted by 'R'.
* The charger is denoted by 'C'. This will be further explained below when we talk about the cleaning robot itself.
* The visited area is denoted by 'V'. It is the place that the robot can visit under certain constraints.  

In short, they can be represented by the following constant variables in our program:
<img width="180" alt="Screenshot 2022-10-02 at 12 18 12" src="https://user-images.githubusercontent.com/19373417/193437617-5e9b0c51-f1f2-443c-baa0-7a391274b698.png">  
The constant variables MAP_HEIGHT and MAP_WIDTH , as defined at the top of the header file, are constants with values of 12. These variables will be changed when we use different maps to grade your program.  
<img width="178" alt="Screenshot 2022-10-02 at 12 18 43" src="https://user-images.githubusercontent.com/19373417/193437634-151d27ff-ae2d-406c-92a6-587f973b0169.png">  
We have also provided extra temperary 2D char array which is EMPTY that you can use when you implement your functions, and we will not check the content of this variable:
<img width="245" alt="Screenshot 2022-10-02 at 12 19 27" src="https://user-images.githubusercontent.com/19373417/193437659-c67b3277-4065-45f5-81f6-7beef6e34998.png">  
You can also define extra temporary arrays inside your recursive functions, if you need to. However, you need to pay extra attention on the depths of the recursive functions, as if there are a lot of memory copies of the maps, the program will easily break down due to a lot of memory has been reserved, then cause stack overflow error.

### 3.2 Cleaning Robot
The robot (represented by the symbol R) has the following features:  
* The robot can only move in four directions: Left, Right, Up, Down; To be specified, it cannot move in the diagonal directions, e.g. Up-Left, Up-Right, Down-Left, Down-Right.  
* The robot can only move to an immediate adjacent cell (i.e. not 2 cells away from the current location).
* The robot will have a battery that stores a certain amount of energy unit.
* If the battery energy is less than 0, the robot can no longer move.
* When the robot reaches a charger, the robot get fully charged at once. To be precise, the robot's battery will be charged to its full capacity.
* The robot knows the details of the whole map, including the blocks and the chargers.
* It knows its status, for example, where the robot is, and how much is the energy stored in the robot. That is useful when the robot needs to decide if it continues to the next un-visited place, or find a charger if needed.  

The corresponding status can be found by the following variables in the main function:  
* <img width="85" alt="Screenshot 2022-10-02 at 12 27 59" src="https://user-images.githubusercontent.com/19373417/193437873-754eefc2-7f49-4a3b-bb50-b934dc3d4756.png">
* <img width="85" alt="Screenshot 2022-10-02 at 12 28 15" src="https://user-images.githubusercontent.com/19373417/193437879-31d573f5-0f8d-4046-9e81-ce5005b035ec.png">
* <img width="120" alt="Screenshot 2022-10-02 at 12 28 27" src="https://user-images.githubusercontent.com/19373417/193437886-ab3edeab-156d-4478-a7fb-9e986d64ab48.png">
* <img width="148" alt="Screenshot 2022-10-02 at 12 28 37" src="https://user-images.githubusercontent.com/19373417/193437891-5539e63d-ee49-4792-b3e7-08c922bc0a47.png">  
They are the local variables in the main function and will be passed to the recursive functions.

### 3.3 Menu
We will use a menu in the main function to call the functions. When an instruction is executed, the menu shows again and you can use to do another actions.
Output:
<p align="center">
<img width="637" alt="Screenshot 2022-10-02 at 12 29 54" src="https://user-images.githubusercontent.com/19373417/193437916-87b905ff-ab38-4ad2-9765-885b079e3e8d.png"></p>  

## 4. Given Functions





Disclaimer: This is a university project about how to solve an **Auto Cleaning Machine** problem with **recursion**, using C++ as required. The description of the problem comes from the Internet and school. However, the coding part is 100% original and I highly value the academic integrity.
