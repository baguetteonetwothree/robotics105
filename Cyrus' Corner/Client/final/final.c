
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "abdrive.h"
#include "simpletext.h"
#include "simpletools.h"
#include "ping.h"
#include "simulator.h"

int square_dist = 132;
//Test code from /Client/test/testIRSensors.c
int getIRLeft(){
  int irLeft = 0;
  for(int dacVal = 0; dacVal < 160; dacVal += 8 ){
      dac_ctr(26, 0, dacVal);
      freqout(11, 1, 38000);
      irLeft += input(10);
    }
  return irLeft;
}

int getIRRight(){
  int irRight = 0;
  for(int dacVal = 0; dacVal < 160; dacVal += 8){
      dac_ctr(27, 1, dacVal);
      freqout(1, 1, 38000);
      irRight += input(2);
    }
  return irRight;
}

int main (){
    simulator_startNewSmokeTrail();
    drive_goto(square_dist, square_dist);
    int i = 0;
    while (i<3){
        int IRLeft = getIRLeft();
        int IRRight =getIRRight();
        print("Left %i" , IRLeft);
        print("Right %i", IRRight);
        drive_goto(square_dist, square_dist);
        i++;
        
    }
    
    return 0;
}