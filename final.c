
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
  if (left < 15) {
    cells[x][y].west = 1;
  } if (right < 15) {
    cells[x][y].east = 1;
  } if (front < 25) {
    cells[x][y].north = 1;
  }
  printf("x val %d |y val %d | north %d | east %d | west %d\n", x,y,cells[x][y].north, cells[x][y].east, cells[x][y].west);
}

void updatePos(char direction){

}
// end of Hiru's corner in Cyrus' corner

int square_dist = 132;

int main (){
  init();
  simulator_startNewSmokeTrail();
  int x = 0;
  int y = -1;
  int i = 0;
  while (i<100){
    drive_goto(square_dist, square_dist);
    int turns;
    // updatePos();
    // y++;
    switch (facing) {
      case 'n':
        y++;
        break;
      case 'e':
        x++;
        break;
      case 's':
        y--;
        break;
      case 'w':
        x--;
        break;
    }
    int IRLeft = dist("LEFT");
    int IRRight = dist("RIGHT");
    int front = ping_cm(8);
    if(isWallSide(IRLeft) && isWallSide(IRRight) && isWallFront(front)){
      drive_goto(50,-49);
      //facing = 's';
      turns = 2;
    }
    if(isWallSide(IRLeft) && isWallFront(front) && !isWallSide(IRRight)){
      drive_goto(25,-24);
      turns = 1;
    }
    if(isWallSide(IRRight) && isWallFront(front) && !isWallSide(IRLeft)){
      drive_goto(-24,25);
      turns = -1;
    }
    if(isWallFront(front) && !isWallSide(IRLeft) && !isWallSide(IRRight)){
      drive_goto(-24,25);
    }



    printf("front %d\n", front);
    makeMap(facing,x,y,IRLeft, IRRight, front);
    // Turn left right code goes here

    printf("Left %i \n" , IRLeft);
    printf("Right %i \n", IRRight);
    i++;

  }

  return 0;
}
