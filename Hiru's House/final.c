
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "abdrive.h"
#include "simpletext.h"
#include "simpletools.h"
#include "ping.h"
#include "simulator.h"

//creating map within program
//if wall present then val will be 1 else 0
char facing = 'n';
struct mazeMap {
  int north;
  int east;
  int south;
  int west;
};

struct mazeMap cells[4][4];

//can't init any other way
void init(){
	for(int i = 0; i < 4; i++){
		for(int j = 0; j< 4; j++){
			cells[i][j].north = 0;
			cells[i][j].east = 0;
			cells[i][j].south = 0;
			cells[i][j].west = 0;
		}
	}
}

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
//Test code from /Client/test/testIRSensors.c
int getIRLeft(){
  int irLeft = 0;
  for(int dacVal = 0; dacVal < 160; dacVal += 8 ){
      dac_ctr(26, 0, dacVal);
      freqout(11, 1, 38000);
      irLeft += input(10);
    }
  // printf("%i\n", irLeft);
  return irLeft;

}

int getIRRight(){
  int irRight = 0;
  for(int dacVal = 0; dacVal < 160; dacVal += 8){
      dac_ctr(27, 1, dacVal);
      freqout(1, 1, 38000);
      irRight += input(2);
    }
  // printf("%i\n", irRight);
  return irRight;
}

int main (){
  init();
  simulator_startNewSmokeTrail();
  int x = 0;
  int y = -1;
  int i = 0;
  while (i<100){
    drive_goto(square_dist, square_dist);
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
    int IRLeft = getIRLeft();
    int IRRight =getIRRight();
    int front = ping_cm(8);
    printf("front %d\n", front);
    makeMap(facing,x,y,IRLeft, IRRight, front);
    // Turn left right code goes here

    // print("Left %i" , IRLeft);
    // print("Right %i", IRRight);
    i++;

  }

  return 0;
}
