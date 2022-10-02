#include <iostream>
#include <cstring>
#include "cleaning_robot.h"
using namespace std;


// Please do all your work in this file. You just need to submit this file.
//Task 1
int findMaximumPlace(int robot_x, int robot_y, int robot_energy, int robot_full_energy, 
   char result_map[MAP_HEIGHT][MAP_WIDTH], char temp_map[MAP_HEIGHT][MAP_WIDTH])
{
   if ( robot_y >= 0 && robot_y <= MAP_HEIGHT && robot_x >= 0 && robot_x <= MAP_WIDTH && robot_energy > 0)
   {       
      //up right down left
      if (result_map[robot_y][robot_x] == 'R'){
         temp_map[0][0] = 1; robot_energy += 1; result_map[robot_y][robot_x] = 'V';}
      if (result_map[robot_y][robot_x] == ' '){
         result_map[robot_y][robot_x] = 'V'; 
         temp_map[0][0] ++;
         } 
      else if (result_map[robot_y][robot_x] == 'C'){
         robot_energy = robot_full_energy;
         result_map[robot_y][robot_x] = 'V';
         temp_map[0][0] ++;
         if ((result_map[robot_y+1][robot_x] != 'B')&&(robot_y+1 <= MAP_HEIGHT)){
            findMaximumPlace(robot_x, robot_y+1, robot_energy, robot_full_energy, 
            result_map, temp_map);}
         if ((result_map[robot_y][robot_x+1] != 'B')&&(robot_x+1 <= MAP_WIDTH)){
            findMaximumPlace(robot_x+1, robot_y, robot_energy, robot_full_energy, 
            result_map, temp_map);}
         if ((result_map[robot_y-1][robot_x] != 'B')&&(robot_y-1 >= 0)){
            findMaximumPlace(robot_x, robot_y-1, robot_energy, robot_full_energy, 
            result_map, temp_map);}
         if ((result_map[robot_y][robot_x-1] != 'B')&&(robot_x-1 >= 0)){
            findMaximumPlace(robot_x-1, robot_y, robot_energy, robot_full_energy, 
            result_map, temp_map);}    
         }

      if ((result_map[robot_y+1][robot_x] != 'B')&&(robot_y+1 <= MAP_HEIGHT)){
         findMaximumPlace(robot_x, robot_y+1, robot_energy-1, robot_full_energy, 
         result_map, temp_map);}
      if ((result_map[robot_y][robot_x+1] != 'B')&&(robot_x+1 <= MAP_WIDTH)){
         findMaximumPlace(robot_x+1, robot_y, robot_energy-1, robot_full_energy, 
         result_map, temp_map);}
      if ((result_map[robot_y-1][robot_x] != 'B')&&(robot_y-1 >= 0)){
         findMaximumPlace(robot_x, robot_y-1, robot_energy-1, robot_full_energy, 
         result_map, temp_map);}
      if ((result_map[robot_y][robot_x-1] != 'B')&&(robot_x-1 >= 0)){
         findMaximumPlace(robot_x-1, robot_y, robot_energy-1, robot_full_energy, 
         result_map, temp_map);}
   }
   else if (robot_energy < 0){return -1;}
   return static_cast<int>(temp_map[0][0]);
}

//Task 2
int minValue(int a, int b, int c, int d){
   return min(min(a,b), min(c,d));
}
/*
int findShortestDistance(int robot_x, int robot_y, int target_x, int target_y, int robot_energy, 
   int robot_full_energy, const char map[MAP_HEIGHT][MAP_WIDTH], char temp_map[MAP_HEIGHT][MAP_WIDTH])
{  
   int up = 0, right = 0, down = 0, left = 0;
   if ( robot_y >= 0 && robot_y <= MAP_HEIGHT && robot_x >= 0 && robot_x <= MAP_WIDTH && robot_energy > 0)
   {  
      if ((map[robot_y-1][robot_x] != 'B')&&(robot_y-1 >= 0)){
         up = findShortestDistance(robot_x, robot_y-1, target_x, target_y, robot_energy-1, 
         robot_full_energy, map, temp_map);}
         

      if ((map[robot_y][robot_x+1] != 'B')&&(robot_x+1 <= MAP_WIDTH)){
         right = findShortestDistance(robot_x+1, robot_y, target_x, target_y, robot_energy-1, 
         robot_full_energy, map, temp_map);}
         

      if ((map[robot_y+1][robot_x] != 'B')&&(robot_y+1 <= MAP_HEIGHT)){
         down = findShortestDistance(robot_x, robot_y+1, target_x, target_y, robot_energy-1, 
         robot_full_energy, map, temp_map);}
         

      if ((map[robot_y][robot_x-1] != 'B')&&(robot_x-1 >= 0)){
         left = findShortestDistance(robot_x-1, robot_y, target_x, target_y , robot_energy-1, 
         robot_full_energy, map, temp_map);}


      if (map[robot_y][robot_x] == 'B'){return 99999;}
      if (map[robot_y][robot_x] == 'C'){robot_energy = robot_full_energy+1;}
      if ((robot_y == target_y) && (robot_x == target_x)){return 1;}
      else return 1+minValue(up, right, down, left);
         
   }
   return 99999;
}
*/
int findShortestDistance(int robot_x, int robot_y, int target_x, int target_y, int robot_energy, 
   int robot_full_energy, const char map[MAP_HEIGHT][MAP_WIDTH], char temp_map[MAP_HEIGHT][MAP_WIDTH])
{   
   if(map[robot_y][robot_x]=='C') {robot_energy = robot_full_energy+1;};
    if(robot_x==target_x&&robot_y==target_y){
        return 1;
    }
    else if(robot_energy==0) return PA2_MAX_PATH;
    else if(map[robot_y][robot_x]=='B'||temp_map[robot_y][robot_x]=='G') return PA2_MAX_PATH;
    temp_map[robot_y][robot_x]='G';//mark the position which robot has been to

    // int left_or_right = (target_x-robot_x);
    // int up_or_down = (target_y-robot_y);

    // int left = findShortestDistance(robot_x-1,robot_y,target_x,target_y,robot_energy-1,robot_full_energy,map,temp_map);
    // int right = findShortestDistance(robot_x+1,robot_y,target_x,target_y,robot_energy-1,robot_full_energy,map,temp_map);
    // int up = findShortestDistance(robot_x,robot_y-1,target_x,target_y,robot_energy-1,robot_full_energy,map,temp_map);
    // int down = findShortestDistance(robot_x,robot_y+1,target_x,target_y,robot_energy-1,robot_full_energy,map,temp_map);

    int ret = PA2_MAX_PATH;
    if(robot_y-1>=0){ret = min(ret,findShortestDistance(robot_x,robot_y-1,target_x,target_y,robot_energy-1,robot_full_energy,map,temp_map));}
    if(robot_x+1<MAP_WIDTH){ret = min(ret,findShortestDistance(robot_x+1,robot_y,target_x,target_y,robot_energy-1,robot_full_energy,map,temp_map));}
    if(robot_y+1<MAP_HEIGHT){ret = min(ret,findShortestDistance(robot_x,robot_y+1,target_x,target_y,robot_energy-1,robot_full_energy,map,temp_map));}
    if(robot_x-1>=0){ret = min(ret,findShortestDistance(robot_x-1,robot_y,target_x,target_y,robot_energy-1,robot_full_energy,map,temp_map));}
    return ret+1;
}
  



/*
int findShortestDistance(int robot_x, int robot_y, int target_x, int target_y, int robot_energy, 
   int robot_full_energy, const char map[MAP_HEIGHT][MAP_WIDTH], char temp_map[MAP_HEIGHT][MAP_WIDTH])
{  
   if ((robot_y == target_y) && (robot_x == target_x)){temp_map[0][0] = 1;}
   if ( robot_y >= 0 && robot_y <= MAP_HEIGHT && robot_x >= 0 && robot_x <= MAP_WIDTH && robot_energy > 0)
   {
      cout << "Current: " << robot_x << robot_y << endl;
      if (map[robot_y][robot_x] == 'C'){robot_energy = robot_full_energy+1;}     
      //up right down left
      if ((map[robot_y-1][robot_x] != 'B')&&(robot_y-1 >= 0)){
         cout << "U" << robot_x << robot_y-1 << endl;
         findShortestDistance(robot_x, robot_y-1, target_x, target_y, robot_energy-1, 
         robot_full_energy, map, temp_map);}
         

      if ((map[robot_y][robot_x+1] != 'B')&&(robot_x+1 <= MAP_WIDTH)){
         cout << "R" << robot_x+1 << robot_y << endl; 
         findShortestDistance(robot_x+1, robot_y, target_x, target_y, robot_energy-1, 
         robot_full_energy, map, temp_map);}
         

      if ((map[robot_y+1][robot_x] != 'B')&&(robot_y+1 <= MAP_HEIGHT)){
         cout << "D" << robot_x << robot_y+1 << endl;
         findShortestDistance(robot_x, robot_y+1, target_x, target_y, robot_energy-1, 
         robot_full_energy, map, temp_map);}
         

      if ((map[robot_y][robot_x-1] != 'B')&&(robot_x-1 >= 0)){
         cout << "L" << robot_x-1 << robot_y << endl;
         findShortestDistance(robot_x-1, robot_y, target_x, target_y , robot_energy-1, 
         robot_full_energy, map, temp_map);}
         
      
      
         
   }
   if ((robot_y == target_y) && (robot_x == target_x)){
      return static_cast<int>(temp_map[0][0]);}
}
*/

//Task 3
int findPathSequence(int robot_x, int robot_y, int target_x, int target_y, int robot_energy, int robot_full_energy, 
   char result_sequence[], const char map[MAP_HEIGHT][MAP_WIDTH], char temp_map[MAP_HEIGHT][MAP_WIDTH])
{

}

//Task 4
int findFarthestPossibleCharger(int robot_x, int robot_y, int robot_original_x, int robot_original_y, 
   int &target_x, int &target_y, int robot_energy, int robot_full_energy, const char map[MAP_HEIGHT][MAP_WIDTH], 
   char temp_map[MAP_HEIGHT][MAP_WIDTH])
{

}