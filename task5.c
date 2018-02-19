#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "simpletools.h"
#include "abdrive.h"
#include "ping.h"

static int LEFT = 0, RIGHT = 1;
static double leftDistanceToWall;
static double rightDistanceToWall;
int STOP_DIST = 10;
int prevLeftIntegral, prevRightIntegral = 0;
int prevLeftError, prevRightError = 0;

int getDistanceFromWall(int wall) {
  low(26);
  low(27);

  int irLeft = 0;
  int irRight = 0;

  for(int dacVal = 0; dacVal < 160; dacVal += 8) {
    dac_ctr(26, 0, dacVal);
    freqout(11, 1, 380000000);
    irLeft += input(10);

    dac_ctr(27, 1, dacVal);
    freqout(1, 1, 380000000);
    irRight += input(2);
  }

  if (wall == LEFT) {
    return irLeft;
  }else{
    return irRight;
  }
}

void averageStartingDistances() {
  int left = 0;
  int right = 0;
  for (int i = 0; i < 10; i++) {
    left += getDistanceFromWall(LEFT);
    right += getDistanceFromWall(RIGHT);
  }

  leftDistanceToWall = left/10;
  rightDistanceToWall = right/10;

  printf( "Left wall - %f\t||   Right wall - %f\n", leftDistanceToWall, rightDistanceToWall);
}

int getDistanceError(int distance, int wall) {
  if(wall == 0){
    return leftDistanceToWall - distance;
  }else{
    return rightDistanceToWall - distance;
  }
}

double proportional(int error){
  double kp = 3.99;
  double output = kp * error;
  return output;
}

double integral(int error, int prevIntegral){
  double ki = 1.19;
  double integral = ki * (prevIntegral + error);
  return integral;
}

int derivative(int error, int prevError){
  double kd = 2;
  double derivative = kd * (error - prevError);
  return derivative;
}

int main() {
  averageStartingDistances();
  int dist = ping_cm(8);
  while (dist > STOP_DIST) {
    dist = ping_cm(8);

    // PID controller
    int leftError = getDistanceError(getDistanceFromWall(LEFT), LEFT);
    int rightError= getDistanceError(getDistanceFromWall(RIGHT), LEFT);

    double leftPSignal = proportional(leftError);
    double rightPSignal = proportional(rightError);
    double leftISignal = integral(leftError, prevLeftIntegral);
    double rightISignal = integral(rightError, prevRightIntegral);
    double leftDSignal = derivative(leftError, prevLeftError);
    double rightDSignal = derivative(rightError, prevRightError);

    double leftControl = leftPSignal + leftDSignal;
    double rightControl = rightPSignal + rightDSignal;

    double control = fabs(leftControl) - fabs(rightControl);

    if (control > 0) {
      /* turn left */
      drive_goto(0,control);
      drive_goto(10,10);
    } else {
      // turn right
      drive_goto(fabs(control),0);
      drive_goto(10,10);
    }
    printf("%d\n", dist);
    printf("%f\n", control);

    prevLeftError = leftError;
    prevRightError = rightError;
    prevLeftIntegral = leftISignal;
    prevRightIntegral = rightISignal;

  }
  return 0;
}
