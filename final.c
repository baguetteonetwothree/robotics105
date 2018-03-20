
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

int route[60][2];
int routeCount = 0;
int listRec = 1; //use to record all cells visited before visiting 3,3

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
  printf("%d\n", facing);
}

int main (){
  init();
  simulator_startNewSmokeTrail();
  int x = 0;
  int y = -1;
  int i = 1;
  int turns;
  drive_goto(33,33);
  while (i){
    drive_goto(square_dist, square_dist);
    printf("turns %d\n", turns);
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


    if (x == 3 && y == 3) {
      listRec = 0;
    }
    // printf("%d\n", listRec);
    // printf("%d\n", facing);

    makeMap(facing,x,y,IRLeft, IRRight, front);

    // add to array
    if (listRec == 1) {
      route[routeCount][0] = x;
      route[routeCount][1] = y;
      for (int i = 0; i < routeCount; i++) {
        for (int j = 0; j < 2; j++) {
          printf("%d ", route[i][j]);
        }
        printf("\n");
      }
      routeCount++;
    }

    //180 turn
    if(isWallSide(IRLeft) && isWallSide(IRRight) && isWallFront(front)){
      drive_speed(25,-25);
      pause(2044);
      drive_speed(0,0);
      pause(100);
      turns = 2;
    }//Turn left if blah blah (fucking write it you bitch)
    else if(isWallSide(IRRight) && !isWallFront(front) && !isWallSide(IRLeft)){
      drive_speed(-25, 25);
      pause(1022);
      drive_speed(0,0);
      pause(100);
      turns = -1;
    } else
    //Turn left
    if(isWallSide(IRRight) && isWallFront(front) && !isWallSide(IRLeft)){
      drive_speed(-25, 25);
      pause(1022);
      drive_speed(0,0);
      pause(100);
      turns = -1;
    } else
    //Turn left
    if(isWallFront(front) && !isWallSide(IRLeft) && !isWallSide(IRRight)){
      drive_speed(-25, 25);
      pause(1022);
      drive_speed(0,0);
      pause(100);
      turns = -1;
    } else
   //Turn Right
    if(isWallSide(IRLeft) && isWallFront(front) && !isWallSide(IRRight)){
      drive_speed(25, -25);
      pause(1022);
      drive_speed(0,0);
      pause(100);
     turns = 1;
    } else {
      turns = 0;
    }



    // printf("front %d\n", front);

    // printf("Left %i \n" , IRLeft);
    // printf("Right %i \n", IRRight);
    i++;

  }

  return 0;
}
