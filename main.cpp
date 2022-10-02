#include <iostream>
#include <cstring>
#include <fstream>
#include "cleaning_robot.h"
using namespace std;

int main()
{
    cout << "Welcome to the cleaning program" << endl;

    char map[MAP_HEIGHT][MAP_WIDTH] = {};
    char temp_map[MAP_HEIGHT][MAP_WIDTH] = {};
    char empty_map[MAP_HEIGHT][MAP_WIDTH] = {};
    char result_map[MAP_HEIGHT][MAP_WIDTH] = {};

    int robot_full_energy = 10;

    int robot_x = 0;
    int robot_y = 0;
    int robot_energy = robot_full_energy;

    int choice = 0;
    int int_result = 0;
    int dest_x = 0, dest_y = 0;

    char result_sequence[MAX_STRING_SIZE] = "";

    bool map_loaded = false;

    do
    {
        cout << "Please select from the following options:" << endl;
        cout << "0: Load map" << endl;
        if (map_loaded)
        {
            cout << "1. Print original map" << endl;
            cout << "2. Print robot details" << endl;
            cout << "3. Display the maximum range for the robot in the current place:" << endl;
            cout << "4. Find the shortest distance from current position to a designated position" << endl;
            cout << "5. Find the shortest distance and the shortest path from current position to a designated position" << endl;
            cout << "6. Find the position of the farthest charger and the shortest distance from that charger" << endl;
        }
        cout << "-1. Exit program" << endl;
        cout << "Please enter your choice: ";

        cin >> choice;
        switch (choice)
        {
        case 0:
            char filename[MAX_STRING_SIZE];
            cout << "Please type the file you want to use: ";
            cin >> filename;

            if (loadMap(filename, map))
            {
                printMap(map);
                map_loaded = true;
                setRobot(robot_x, robot_y, robot_full_energy, map);
                robot_energy = robot_full_energy;
                printMap(map);
            }
            else
            {
                cout << "Cannot load map. Please check if the file exists." << endl;
            }
            break;
        case 1:
            printMap(map);
            break;

        case 2:
            cout << "Robot position: (" << robot_x << "," << robot_y << ")" << endl;
            cout << "Robot energy: " << robot_energy << "/" << robot_full_energy << endl;
            break;
        case 3:
            copyMap(result_map, map);
            copyMap(temp_map, empty_map);
            int_result = findMaximumPlace(robot_x, robot_y, robot_energy, robot_full_energy, result_map, temp_map);
            cout << int_result << endl;
            cout << "The result map will be:" << endl;
            printMap(result_map);
            break;
        case 4:
            cout << "Please enter the target x and y, separated by space: ";
            cin >> dest_x >> dest_y;
            copyMap(temp_map, empty_map);
            int_result = findShortestDistance(robot_x, robot_y,
                                              dest_x, dest_y, robot_energy, robot_full_energy, map, temp_map);

            if (int_result >= PA2_MAX_PATH)
            {
                cout << "The destination is unreachable." << endl;
            }
            else
            {
                cout << int_result;
            }
            break;
        case 5:
            cout << "Please enter the target x and y, separated by space: ";
            cin >> dest_x >> dest_y;
            copyMap(temp_map, empty_map);
            int_result = findPathSequence(robot_x, robot_y,
                                          dest_x, dest_y,
                                          robot_energy, robot_full_energy, result_sequence,
                                          map, temp_map);
            if (int_result >= PA2_MAX_PATH)
            {
                cout << "The destination is unreachable." << endl;
            }
            else
            {
                cout << int_result << ":" << result_sequence << endl;
            }
            break;
        case 6:
            int target_x = -1, target_y = -1;
            copyMap(temp_map, empty_map);
            int_result = findFarthestPossibleCharger(robot_x, robot_y, robot_x, robot_y, target_x, target_y, robot_energy, robot_full_energy, map, temp_map);

            if (int_result > -1)
            {
                cout << "The farthest position is (" << target_x << ":" << target_y << ")"
                     << " and the distance is " << int_result << endl;
            }
            else
            {
                cout << "Cannot find" << endl;
            }
        }
        cout << endl;
    } while (choice != -1);
    cout << "Program ends." << endl;
    return 0;
}
