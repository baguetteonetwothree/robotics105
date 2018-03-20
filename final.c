
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "abdrive.h"
#include "simpletext.h"
#include "simpletools.h"
#include "ping.h"
#include "simulator.h"
#include "init.h"
#include "sensors.h"

//setting up map maker
void makeMap(char direction, int x,int y ,int left, int right, int front){
  if (left < 10) {
    cells[x][y].west = 1;
  } if (right < 10) {
    cells[x][y].east = 1;
  } if (front < 25) {
    cells[x][y].north = 1;
  }
  printf("x val %d |y val %d | north %d | east %d | west %d\n", x,y,cells[x][y].north, cells[x][y].east, cells[x][y].west);
}
// end of Hiru's corner in Cyrus' corner


void changeNewDirection(currentFacing, numOfTurns){
  facing = (numOfTurns + currentFacing) % 4;
  if (facing < 0) {facing += 4;}
}

int main (){
  init();
  simulator_startNewSmokeTrail();
  int x = 0;
  int y = -1;
  int i = 1;
  drive_goto(33,33);
  while (i){
    // if at cells (3,0) get currenting facing, find the diif current and 3 change facing to 3
    drive_goto(square_dist, square_dist);
    int turns;
    changeNewDirection(facing, turns);

    switch (facing) {
      case 0:
        y++;
        break;
      case 1:
        x++;
        break;
      case 2:
        y--;
        break;
      case 3:
        x--;
        break;
    }
    int IRLeft = dist("LEFT");
    int IRRight = dist("RIGHT");
    int front = ping_cm(8);

    makeMap(facing,x,y,IRLeft, IRRight, front);
    //180
    if(isWallSide(IRLeft) && isWallSide(IRRight) && isWallFront(front)){
      //drive_goto(50,-49);
      //facing = 's';
      printf("Left %i \n", IRLeft);
      printf("Right %i \n", IRRight);
      printf("Front %i \n", front);
      drive_speed(25,-25);
      pause(2044);
      drive_speed(0,0);
      pause(100);
      turns = 2;
      continue;
    }
 
    //Turn left
    if(isWallSide(IRRight) && !isWallFront(front) && !isWallSide(IRLeft)){
      //drive_goto(-24,25);
      printf("Left %i \n", IRLeft);
      printf("Right %i \n", IRRight);
      printf("Front %i \n", front);
      drive_speed(-25, 25);
      pause(1022);
      drive_speed(0,0);
      pause(100);
      turns = -1;
      continue;
    }


    //Turn left
    if(isWallSide(IRRight) && isWallFront(front) && !isWallSide(IRLeft)){
      //drive_goto(-24,25);
      printf("Left %i \n", IRLeft);
      printf("Right %i \n", IRRight);
      printf("Front %i \n", front);
      drive_speed(-25, 25);
      pause(1022);
      drive_speed(0,0);
      pause(100);
      turns = -1;
      continue;
    }
    //Turn left
    if(isWallFront(front) && !isWallSide(IRLeft) && !isWallSide(IRRight)){
      //drive_goto(-24,25);
      printf("Left %i \n", IRLeft);
      printf("Right %i \n", IRRight);
      printf("Front %i \n", front);
      drive_speed(-25, 25);
      pause(1022);
      drive_speed(0,0);
      pause(100);
      turns = -1;
      continue;
    }

   //Turn Right
    if(isWallSide(IRLeft) && isWallFront(front) && !isWallSide(IRRight)){
      //drive_goto(25,-24);
      printf("Left %i \n", IRLeft);
      printf("Right %i \n", IRRight);
      printf("Front %i \n", front);
      drive_speed(25, -25);
      pause(1022);
      drive_speed(0,0);
      pause(100);
     turns = 1;
      continue;
    }

    // printf("front %d\n", front);
    
    // printf("Left %i \n" , IRLeft);
    // printf("Right %i \n", IRRight);
    i++;

  }

  return 0;
}
