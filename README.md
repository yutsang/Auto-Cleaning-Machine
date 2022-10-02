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
We have the following given functions, which are mainly used in the main function:  
* <img width="563" alt="Screenshot 2022-10-02 at 13 06 01" src="https://user-images.githubusercontent.com/19373417/193438807-7cbafff7-e244-46bb-a167-571be954cf9f.png">  
This helps to load the map data from the text file in a better manner. Extra characters in the line will be excluded. And this will also pad with ' ' if the line is less than MAP_WIDTH.
* <img width="589" alt="Screenshot 2022-10-02 at 13 06 45" src="https://user-images.githubusercontent.com/19373417/193438836-281cc48f-ded0-4973-b53b-61950ee82db9.png">  
This loads the map data from a text file filename. When the file is not present, the function returns false; else the file is loaded to the program and it returns true.  
* <img width="649" alt="Screenshot 2022-10-02 at 13 07 16" src="https://user-images.githubusercontent.com/19373417/193438853-7d52cd85-0ea5-479b-aff0-65e3ae1d92cb.png">  
This copies original_map to target_map.  
* <img width="306" alt="Screenshot 2022-10-02 at 13 07 40" src="https://user-images.githubusercontent.com/19373417/193438862-8a866d90-a12c-4530-970a-53f1b41308d6.png">  
This prints the content in map.  
<img width="90" alt="Screenshot 2022-10-02 at 13 08 20" src="https://user-images.githubusercontent.com/19373417/193438876-25261c18-cb94-4312-b088-f0094ca9c17e.png">  
* <img width="857" alt="Screenshot 2022-10-02 at 13 09 13" src="https://user-images.githubusercontent.com/19373417/193438907-70d55086-0eee-42e0-92c6-30eab6d6e0a3.png">  
This sets the position and the battery capacity of the robot.  
<img width="394" alt="Screenshot 2022-10-02 at 13 10 16" src="https://user-images.githubusercontent.com/19373417/193438928-f0337fb0-6cc4-4dfe-b4ac-3f7072d039f6.png">  

## 5. Functions
### 5.1 Principle on Searching Directions
In this assignment, the robot can only search for the surronding blocks clockwisely by the following order: starting in upward direction, then rightward direction, then downward direction, finally leftward direction. That means the order must be:
  1. Up  
  2. Right  
  3. Down  
  4. Left
Remember that in this assignment, the robot cannot go in diagonal directions.  

### 5.2 TODO Functions
Here are the 4 functions that you need to implement for this assignment. They are useful when the robot needs to determine what the next target is and how to go to the next target in an effective way.  

### 5.2.1  
<img width="622" alt="Screenshot 2022-10-02 at 13 15 55" src="https://user-images.githubusercontent.com/19373417/193439076-e4de7372-3ca8-4851-aabb-46e520bdb301.png">  
This recursive function finds the maximum area that the robot may visit with its battery fully used, and max mark the area in the result_map. Also, it returns the number of positions that can be VISITED by the robot.  
This function will see if the robot can reach a particular position. If yes, the function should change the character at this position to 'V' to indicate that it can be VISITED. Then, the function will try to further determine if the robot can move (visit) from here, via recursive calls of the same function, to the neighboring positions in the 4 directions: up, right, down, left.  
Every move of the robot will consume 1 unit of energy from robot_energy, but if the robot
reaches to a charger, the robot_enery should be resumed to robot_full_energy.  
We keep doing that until the robot can no longer move based on the energy stored in the robot.  

For example:  
  * If the robot (5, 5) has 3 energy units remaining when this function is first called, the result_map will be this (To make it more clear, the 'V' in the illustration has been highlighted with red):  
    * <img width="96" alt="Screenshot 2022-10-02 at 13 17 30" src="https://user-images.githubusercontent.com/19373417/193439111-e9438cf9-7ed2-4a7c-8faa-7226b8c52eeb.png"> 
    * And the function returns 21, which means these 21 positions may be reached by the robot.
  * If the robot (5, 5) has 4 energy units remaining when this function is first called, the result_map will be this:
    * <img width="96" alt="Screenshot 2022-10-02 at 13 18 42" src="https://user-images.githubusercontent.com/19373417/193439148-dcb1d254-791d-48ec-b5fa-48bd0f381f47.png">
    * And it return 58  
You can see that when the robot reaches a charger, the robot gets charged up, and thus, more positions can be visited by the robot.  

### 5.2.2  
<img width="617" alt="Screenshot 2022-10-02 at 13 19 47" src="https://user-images.githubusercontent.com/19373417/193439180-e6dfa4ad-07c7-4ff8-8f8b-76e7158747f8.png">    
This recursive function finds the shortest distance from the current robot position (robot_x, robot_y) to the target position (target_x, target_y), based on the constraints of energy, chargers and blocked areas. If the robot cannot go there within the robot_energy, it returns the constant MAX_PATH PA2_MAX_PATH (Updated: Oct 24 12:50pm) and that indicates that the specified position is unreachable. But note that the robot will get fully charged again when it reaches a charger (i.e. robot_energy will be resumed to the value of robot_full_energy).  
For Task 2, we will do a max battery cap as 5. (robot_full_energy will not greater than 5 for Task 2, Task 3 and Task 4)  
For example: If the robot has 5 units of energy, and using the map,  
<img width="83" alt="Screenshot 2022-10-02 at 13 21 13" src="https://user-images.githubusercontent.com/19373417/193439224-ee173e04-35ae-4220-ba13-fb6ef6753aa0.png">  
  * If the target is (5, 5) (that means the same with the robot), the return value is 1.
  * If the target is (5, 6), the return value is 2.
  * If the target is (6, 6), the return value is 3.
  * If the target is (6, 7), the return value is 4.
  * If the target is (7, 5), the return value is 3.
  * If the target is (3, 3), the return value is 5.
  * If the target is (5, 3), the return value is 5.
  * If the target is (2, 4), the return value is MAX_PATH PA2_MAX_PATH, that means it is unreachable (as it is BLOCKED).
  * If the target is (5, 9), the return value is 7, as to go there, the robot has to use the charger in (4, 9).
  *If the target is (3, 11), the return value is 11, as to go there, the robot has to use the charger in (4, 9).  

For example: If the robot has 5 units of energy, and using the map,  
<img width="83" alt="Screenshot 2022-10-02 at 13 22 55" src="https://user-images.githubusercontent.com/19373417/193439272-9820f8a3-3a3e-4b3c-b530-14d10c43d8cd.png">  

  * If the target is (5, 5), the return value is 2.
  * If the target is (5, 6) (that means the same with the robot), the return value is 1.
  * If the target is (6, 6), the return value is 2.
  * If the target is (6, 7), the return value is 3.
  * If the target is (3, 3), the return value is 6.
  * If the target is (5, 3), the return value is 6.
  * If the target is (2, 4), the return value is MAX_PATH PA2_MAX_PATH, that means it is unreachable (as it is BLOCKED).
  * If the target is (5, 9), the return value is 6, as to go there, the robot has to use the charger in (4, 9).
  * If the target is (3, 11), the return value is 10, as to go there, the robot has to use the charger in (4,9).
  
### 5.2.3  
<img width="592" alt="Screenshot 2022-10-02 at 13 24 10" src="https://user-images.githubusercontent.com/19373417/193439311-cebe1037-f95b-4d26-b5c4-5a74bcf4c7ad.png">  
This recursive function finds the sequence of moves which gives the shortest distance from the current robot position (robot_x, robot_y) to the target position (target_x, target_y), based on the constraints of energy, chargers and blocked areas. If the robot cannot go there within the robot_energy, it returns the constant PA2_MAX_PATH  and that indicates that position is unreachable. But note that the robot will get fully charged again when it reaches a charger (i.e. robot_energy will be resumed to the value of robot_full_energy).  
Remember that result_sequence has to be C-String. That means it should be null-terminated. For Task 3, we will do a max battery cap as 5. (robot_full_energy will not greater than 5 for Task 2, Task 3 and Task 4)  
For example: If the robot has 5 unit of energy, and using the map,  
<img width="86" alt="Screenshot 2022-10-02 at 13 25 55" src="https://user-images.githubusercontent.com/19373417/193439376-fc943605-f127-493b-a134-e53bb764bbdf.png">  
  * If the target is (5, 5) (that means the same with the robot), the return value is 1, and the variable result_sequence is T.
  * If the target is (5, 6), the return value is 2, and the variable result_sequence is DT.
  * If the target is (6, 6), the return value is 3, and the variable result_sequence is RDT.
  * If the target is (6, 7), the return value is 4, and the variable result_sequence is RDDT.
  * If the target is (3, 3), the return value is 5, and the variable result_sequence is LUULT.
  * If the target is (5, 3), the return value is 5, and the variable result_sequence is RUULT.
  * If the target is (2, 4), the return value is PA2_MAX_PATH, that means it is unreachable (as it is BLOCKED).
  * If the target is (5, 9), the return value is 7, and the variable result_sequence is DDLDDRT.
  * If the target is (3, 11), the return value is 11, and the variable result_sequence is DDLDDRDDLLT.
  
For example: If the robot has 5 unit of energy, and using the map,  
<img width="86" alt="Screenshot 2022-10-02 at 13 27 30" src="https://user-images.githubusercontent.com/19373417/193439418-ef56a3fd-6f19-4f11-b388-5fca5983fdd5.png">  
  * If the target is (5, 5) , the return value is 2, and the variable
result_sequence is UT.
  * If the target is (5, 6) (that means the same with the robot), the return value is 1, and the variable result_sequence is T.
  * If the target is (6, 6), the return value is 2, and the variable result_sequence is RT.
  * If the target is (6, 7), the return value is 3, and the variable result_sequence is RDT.
  * If the target is (3, 3), the return value is 6, and the variable result_sequence is ULUULT.
  * If the target is (5, 3), the return value is 6, and the variable result_sequence is URUULT.
  * If the target is (2, 4), the return value is PA2_MAX_PATH, that means it is unreachable (as it is BLOCKED).
  * If the target is (5, 9), the return value is 6, and the variable result_sequence is DLDDRT.
  * If the target is (3, 11), the return value is 10, and the variable result_sequence is DLDDRDDLLT.  
  
## 5.2.4  
<img width="628" alt="Screenshot 2022-10-02 at 13 29 35" src="https://user-images.githubusercontent.com/19373417/193439484-21f299f6-a616-4cf4-9c62-6ae982a87011.png">  
The function will scan through the walkable area and then determine whether there is any position that matches with a charger.  
If there is at least one charger, then the farthest position will be returned by the reference variables target_x and target_y, together with returning the shortest distance between the robot's original position to that position.  
When a charger is not found or none of the chargers can be reached by the robot under the energy constraint, the function returns -1 and we do not care about the value of target_x and target_y.  
If there are different results for considering the 're-charge' case and 'non-recharge' case, both of them will be treated as correct. If there is a discrepency among 'recharge' case and 'non-recharge' case occurs on that test-case and you can produce one of the 2 outputs, then you will get the score on that test case.  
For Task 4, we will do a max battery cap as 5. (robot_full_energy will not greater than 5 for Task 2, Task 3 and Task 4)  

For example: If the robot has 5 units of energy, and using the map,  
<img width="84" alt="Screenshot 2022-10-02 at 13 30 56" src="https://user-images.githubusercontent.com/19373417/193439522-c850fd6d-0ba6-4589-8339-b366d238ca5b.png">  
  * The farthest charger from Point X (5, 5) is Charger (4, 9) and the distance is 6
  * The farthest charger from Point Y (5, 6) is Charger (4, 9) and the distance is 5 
  * The farthest charger from Point Z (4, 5) is Charger (7, 7) and the distance is 6 
    * It is not Charger (4, 9) as distance between Point Z (4, 5) to Charger (7,7) and that between Point Z (4, 5) to Charger (4, 9) are the same. But in this function, the first point found will be returned.  
    
Remember that you can make good use of your previous implemented functions to finish this task.


Disclaimer: This is a university project about how to solve an **Auto Cleaning Machine** problem with **recursion**, using C++ as required. The description of the problem comes from the Internet and school. However, the coding part is 100% original and I highly value the academic integrity.
