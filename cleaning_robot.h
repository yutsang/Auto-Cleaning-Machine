/* COMP2011 Fall 2021 Programming Assignment 2 */

#include <iostream>
#include <cstring>
#include <fstream>
using namespace std;

const int MAP_WIDTH = 12;
const int MAP_HEIGHT = 12;

const int PA2_MAX_PATH = MAP_WIDTH * MAP_HEIGHT;

const int MAX_STRING_SIZE = 100;

const char AVAILABLE = ' ';
const char BLOCKED = 'B';
const char ROBOT = 'R';
const char CHARGER = 'C';
const char VISITED = 'V';

/*** Given Functions ***/

bool loadMap(const char filename[MAX_STRING_SIZE], char map_to_load[MAP_HEIGHT][MAP_WIDTH]);
// This helps to load the map data from the text file in a better manner. Extra characters in the line will be excluded.
//      And this will also pad with ' ' if the line is less than MAP_WIDTH.

void unifyMapLine(char target_map_line[MAP_WIDTH], const char map_line[MAP_WIDTH + 1]);
// This loads the map data from a text file filename.
//      When the file is not present, the function returns false; else the file is loaded to the program and it returns true.

void copyMap(char target_map[MAP_HEIGHT][MAP_WIDTH], const char original_map[MAP_HEIGHT][MAP_WIDTH]);
// This copies original_map to target_map.

void printMap(char map[MAP_HEIGHT][MAP_WIDTH]);
// This prints the content in map.

void setRobot(int &robot_init_x, int &robot_init_y, int &robot_full_energy, char map[MAP_HEIGHT][MAP_WIDTH]);
// This sets the position and the battery capacity of the robot.

/*** TODO functions ***/

int findMaximumPlace(int robot_x, int robot_y, int robot_energy, int robot_full_energy, 
                     char result_map[MAP_HEIGHT][MAP_WIDTH], char temp_map[MAP_HEIGHT][MAP_WIDTH]);
// This recursive function finds the maximum area that the robot may visit with its battery fully used, and marked the area in the result_map.
//      Also, it returns the number of positions that can be VISITED by the robot.
// Parameters:
// 	robot_x: the x coordinate of the robot
// 	robot_y: the y coordinate of the robot
// 	robot_energy: the current energy of the robot
// 	robot_full_energy: the full capacity of robot energy
// 	result_map: the 2d array with the map information and is to be updated with the marking of visitable area of the robot 
// 	temp_map: extra temperary 2D char array, optional for you to use 
// Return Value:
// 	the total number of positions that can be visited by the robot

int findShortestDistance(int robot_x, int robot_y, int target_x, int target_y, int robot_energy, 
                         int robot_full_energy, const char map[MAP_HEIGHT][MAP_WIDTH], char temp_map[MAP_HEIGHT][MAP_WIDTH]);
// This recursive function finds the shortest distance from the current robot position (robot_x, robot_y) to the target position (target_x, target_y),
//          based on the constraints of energy, chargers and blocked areas.
//      If the robot cannot go there within the robot_energy,
//          it returns the constant PA2_MAX_PATH and that indicates that the specified position is unreachable.
// Parameters:
// 	robot_x: the x coordinate of the robot
// 	robot_y: the y coordinate of the robot
// 	target_x: the x coordinate of the target
// 	target_y: the y coordinate of the target 
// 	robot_energy: the current energy of the robot
// 	robot_full_energy: the full capacity of robot energy
// 	result_map: the 2d array with the map information 
// 	temp_map: extra temperary 2D char array, optional for you to use 
// Return Value:
// 	the distance of the shortest path between the robot and the target 
// 	if the target cannot be reached, the constant PA2_MAX_PATH is returned  

int findPathSequence(int robot_x, int robot_y, int target_x, int target_y, int robot_energy, 
                     int robot_full_energy, char result_sequence[], const char map[MAP_HEIGHT][MAP_WIDTH], char temp_map[MAP_HEIGHT][MAP_WIDTH]);
// This recursive function finds the sequence of moves which gives the shortest distance from the current robot position (robot_x, robot_y) to the target position (target_x, target_y),
//          based on the constraints of energy, chargers and blocked areas. target_y), based on the constraints of energy, chargers and blocked areas.
//      If the robot cannot go there within the robot_energy,
//          it returns the constant PA2_MAX_PATH and that indicates that that position is unreachable.
// Parameters:
// 	robot_x: the x coordinate of the robot
// 	robot_y: the y coordinate of the robot
// 	target_x: the x coordinate of the target
// 	target_y: the y coordinate of the target 
// 	robot_energy: the current energy of the robot
// 	robot_full_energy: the full capacity of robot energy
// 	result_sequence: the sequence of moves that gives the shortest path (Note: it has to be a C-String)
// 	map: the 2d array with the map information 
// 	temp_map: extra temperary 2D char array, optional for you to use 
// Return Value:
// 	the distance of the shortest path between the robot and the target
// 	if the target cannot be reached, the constant PA2_MAX_PATH is returned  

int findFarthestPossibleCharger(int robot_x, int robot_y, int robot_original_x, int robot_original_y, 
                                int &target_x, int &target_y, int robot_energy, int robot_full_energy,
                                const char map[MAP_HEIGHT][MAP_WIDTH], char temp_map[MAP_HEIGHT][MAP_WIDTH]);
//  The function will scan through the walkable area and then determine whether there is any position that matches with a charger.
//      If there is at least one charger, then the farthest position will be returned by the reference variables target_x and target_y,
//          together with returning the shortest distance between the robot's original position to that position.
//      When a charger is not found or none of the chargers can be reached by the robot under the energy constraint,
//          the function returns -1 and we do not care about the value of target_x and target_y.
// Parameters:
// 	robot_x: the current x coordinate of the robot
// 	robot_y: the current y coordinate of the robot
// 	robot_original_x: the initial x coordinate of the robot
// 	robot_original_y: the initial y coordinate of the robot
// 	target_x: to store the x coordinate of the farthest charger if found
// 	target_y: to store the y coordinate of the farthest charger if found 
// 	robot_energy: the current energy of the robot
// 	robot_full_energy: the full capacity of robot energy
// 	map: the 2d array with the map information 
// 	temp_map: extra temperary 2D char array, optional for you to use 
// Return Value:
// 	the distance of the shortest path between the robot and the farthest charger
// 	if no charger is reachable, -1 is returned 


