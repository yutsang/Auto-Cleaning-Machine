#include <iostream>
#include <cstring>
#include <fstream>
#include "cleaning_robot.h"
using namespace std;

// Please do not modify this file

void unifyMapLine(char target_map_line[MAP_WIDTH], const char map_line[MAP_WIDTH + 1])
{
    for (int i = 0; i < MAP_WIDTH; i++)
    {
        if (map_line[i] == '\0')
        {
            target_map_line[i] = ' ';
        }
        else
        {
            target_map_line[i] = map_line[i];
        }
    }
}
bool loadMap(const char filename[MAX_STRING_SIZE], char map_to_load[MAP_HEIGHT][MAP_WIDTH])
{
    fstream ifs(filename);
    if (ifs)
    {
        int counter = 0;
        while (!(ifs.eof() || counter >= MAP_HEIGHT))
        {
            char line[MAX_STRING_SIZE] = "";
            ifs.getline(line, MAX_STRING_SIZE);
            unifyMapLine(map_to_load[counter], line);
            counter++;
        }
        char empty_line[MAX_STRING_SIZE] = "";
        for (int padding = counter; padding < MAP_HEIGHT; padding++)
        {
            unifyMapLine(map_to_load[padding], empty_line);
        }
        return true;
    }
    return false;
}

void copyMap(char target_map[MAP_HEIGHT][MAP_WIDTH], const char original_map[MAP_HEIGHT][MAP_WIDTH])
{
    for (int i = 0; i < MAP_WIDTH; i++)
    {
        for (int j = 0; j < MAP_HEIGHT; j++)
        {
            target_map[j][i] = original_map[j][i];
        }
    }
}

void printMap(char map[MAP_HEIGHT][MAP_WIDTH])
{
    cout << "  ";
    for (int i = 0; i < MAP_WIDTH; i++)
    {
        cout << i % 10;
    }
    cout << "  " << endl;

    cout << " ";
    for (int i = 0; i < MAP_WIDTH + 2; i++)
    {
        cout << "-";
    }
    cout << endl;

    for (int j = 0; j < MAP_HEIGHT; j++)
    {
        cout << j % 10 << "|";
        for (int i = 0; i < MAP_WIDTH; i++)
        {
            cout << map[j][i];
        }
        cout << "|" << endl;
    }
    cout << " ";
    for (int i = 0; i < MAP_WIDTH + 2; i++)
    {
        cout << "-";
    }
    cout << endl;
}

void setRobot(int &robot_init_x, int &robot_init_y, int &robot_full_energy, char map[MAP_HEIGHT][MAP_WIDTH])
{
    if (map[robot_init_y][robot_init_x] == ROBOT)
        map[robot_init_y][robot_init_x] = AVAILABLE;

    cout << "Please give the x and the y of the robot, with space to separate: ";
    cin >> robot_init_x >> robot_init_y;

    map[robot_init_y][robot_init_x] = ROBOT;

    cout << "Please give battery capacity of the robot: ";
    cin >> robot_full_energy;

    return;
}
