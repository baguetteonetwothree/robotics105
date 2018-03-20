#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "abdrive.h"
#include "simpletext.h"
#include "simpletools.h"


int dist(char WALL[]){
    if (strcmp(WALL, "LEFT") == 0){
        int irLeft = 0;
        for(int dacVal = 0; dacVal < 160; dacVal += 8 ){
            dac_ctr(26, 0, dacVal);
            freqout(11, 1, 38000);
            irLeft += input(10);
        }
        // printf("%i\n", irLeft);
        return irLeft;
    }else if(strcmp(WALL,"RIGHT") == 0){
        int irRight = 0;
        for(int dacVal = 0; dacVal < 160; dacVal += 8){
            dac_ctr(27, 1, dacVal);
            freqout(1, 1, 38000);
            irRight += input(2);
        }
        // printf("%i\n", irRight);
        return irRight;
    } else {
      printf("ERROR: Invalid signal recieved from wall sensor\n");
    }
}

int isWallSide(int distance){
    if (distance < 15){
        return 1;
    }else{
        return 0;
    }

}

int isWallFront(int distance){
    return distance < 25;
}
