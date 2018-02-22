#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "simpletools.h"
#include "abdrive.h"
#include "ping.h"
#include "simulator.h"

static int LEFT = 0, RIGHT = 1;
static double leftDistanceToWall;
static double rightDistanceToWall;
int STOP_DIST = 20;
int prevLeftIntegral, prevRightIntegral = 0;
int prevLeftError, prevRightError = 0;

struct Element* linkList = NULL;

struct Element {
  int data;
  struct Element *next;
};

void append(struct Element** head_ref, int new_data) {
    /* 1. allocate node */
    struct Element* new_node = (struct Element*) malloc(sizeof(struct Element));
    struct Element *last = *head_ref;  /* used in step 5*/
    /* 2. put in the data  */
    new_node->data  = new_data;
    /* 3. This new node is going to be the last node, so make next of
          it as NULL*/
    new_node->next = NULL;
    /* 4. If the Linked List is empty, then make the new node as head */
    if (*head_ref == NULL) {
       *head_ref = new_node;
       return;
    }
    /* 5. Else traverse till the last node */
    while (last->next != NULL)
        last = last->next;
    /* 6. Change the next of last node */
    last->next = new_node;
    return;
}

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
  double kp = 2.5;
  double output = kp * error;
  return output;
}

int derivative(int error, int prevError){
  double kd = 2;
  double derivative = kd * (error - prevError);
  return derivative;
}

void push(struct Element** head_ref, int new_data)
{
    /* 1. allocate node */
    struct Element* new_node = (struct Element*) malloc(sizeof(struct Element));
    /* 2. put in the data  */
    new_node->data  = new_data;
    /* 3. Make next of new node as head */
    new_node->next = (*head_ref);
    /* 4. move the head to point to the new node */
    (*head_ref)    = new_node;
}

void drive(left, right) {
  drive_goto(left, right);
  append(&linkList, left);
  append(&linkList, right);
}

void printList(struct Element *node)
{
  while (node != NULL)
  {
     printf(" %d ", node->data);
     node = node->next;
  }
}

int main() {
  averageStartingDistances();
  int dist = ping_cm(8);
  simulator_startNewSmokeTrail();
  while (dist > STOP_DIST) {
    dist = ping_cm(8);

    // PID controller
    int leftError = getDistanceError(getDistanceFromWall(LEFT), LEFT);
    int rightError= getDistanceError(getDistanceFromWall(RIGHT), LEFT);

    double leftPSignal = proportional(leftError);
    double rightPSignal = proportional(rightError);
    double leftDSignal = derivative(leftError, prevLeftError);
    double rightDSignal = derivative(rightError, prevRightError);

    double leftControl = leftPSignal + leftDSignal;
    double rightControl = rightPSignal + rightDSignal;

    double control = fabs(leftControl) - fabs(rightControl);

    if (control > 0) {
      /* turn left */
      drive(0,control);
    } else {
      // turn right
      drive(fabs(control),0);
    }
    drive(10,10);
    printf("%d\n", dist);
    printf("%f\n", control);

    prevLeftError = leftError;
    prevRightError = rightError;
  }
  int uturn = (int)round(180 * 0.284);
  drive_goto(-uturn,uturn);
  struct Element* reversedLinkList = NULL;
  while (linkList != NULL) {
    push(&reversedLinkList, linkList->data);
    linkList = linkList->next;
  }
  while (reversedLinkList != NULL) {
    int left = reversedLinkList->data;
    reversedLinkList = reversedLinkList->next;
    int right = reversedLinkList->data;
    drive_goto(left,right);
    reversedLinkList = reversedLinkList->next;
  }
  simulator_stopSmokeTrail();
  return 0;
}
