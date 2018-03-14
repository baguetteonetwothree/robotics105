// This implements a wrapper for the abdrive library

#include "abdrive.h"

#include <sstream>
#include <cstdio>
#include <cmath>

#include "Console.hpp"
#include "launcher.hpp"

//#include "goto_test.c"

using namespace ::std;

static int cog = 0;

// Stored locally to validate results
static int abd_speedLimit = 128;

void drive_feedback(int enabled)
{
  WARN_STREAM_NAMED("abdrive", __FUNCTION__ << " stub implementation");
}

void drive_trim(int enabled)
{
  WARN_STREAM_NAMED("abdrive", __FUNCTION__ << " stub implementation");
}

void drive_trimSet(int direction, int side, int value)
{
  WARN_STREAM_NAMED("abdrive", __FUNCTION__ << " stub implementation");
}

void drive_trimDisplay(void)
{
  WARN_STREAM_NAMED("abdrive", __FUNCTION__ << " stub implementation");
}

void drive_displayInterpolation(void)
{
  WARN_STREAM_NAMED("abdrive", __FUNCTION__ << " stub implementation");
}

void drive_encoderPins(int encPinLeft, int encPinRight)
{
  WARN_STREAM_NAMED("abdrive", __FUNCTION__ << " stub implementation");
}

void drive_servoPins(int servoPinLeft, int servoPinRight)
{
  WARN_STREAM_NAMED("abdrive", __FUNCTION__ << " stub implementation");
}

void drive_speed(int left, int right)
{
  stringstream message;
  message << "ROBOT " << robotHandle << " drive_speed " << left << " " << right << "\n";

  // Send it out
  string result = serverConnection.sendMessageAndReturnReply(message.str());
}

void drive_ramp(int left, int right)
{
  // Check commands are okay
  if ((abs(left) > abd_speedLimit) || (abs(left) > abd_speedLimit))
    {
      ERROR_STREAM_NAMED("abdrive", __FUNCTION__ << " The requested speed for drive_ramp exceeds the speed limit; this will hang");
      ERROR_STREAM_NAMED("abdrive", __FUNCTION__ << " left=" << left << "; right=" << right << "; speedLimit=" << abd_speedLimit);
    }
  
  stringstream message;
  message << "ROBOT " << robotHandle << " drive_ramp " << left << " " << right << "\n";
  string result = serverConnection.sendMessageAndReturnReply(message.str());
}

void drive_rampStep(int left, int right)
{
  stringstream message;
  message << "ROBOT " << robotHandle << " drive_rampStep " << left << " " << right << "\n";
  string result = serverConnection.sendMessageAndReturnReply(message.str());
}

void drive_setRampStep(int stepsize)
{
  stringstream message;
  message << "ROBOT " << robotHandle << " drive_setRampStep " << stepsize << "\n";
  string result = serverConnection.sendMessageAndReturnReply(message.str());
}

void drive_distance(int left, int right)
{
  stringstream message;
  message << "ROBOT " << robotHandle << " drive_distance " << left << " " << right << "\n";
  string result = serverConnection.sendMessageAndReturnReply(message.str());
}

void drive_close(void)
{
  INFO_STREAM_NAMED("abdrive", __FUNCTION__ << " Invoked");
  stringstream message;
  message << "ROBOT " << robotHandle << " drive_close\n";
  serverConnection.sendMessageAndReturnReply(message.str());
  cog = 0;
}

int drive_open()
{
  WARN_STREAM_NAMED("abdrive", __FUNCTION__ << " CHECK RETURN VALUE!");
  cog = 1;
  return cog;
}

void drive_setMaxSpeed(int speed)
{
  // Check that the argument is good
  if (speed < 1)
    {
      WARN_STREAM_NAMED("abdrive", __FUNCTION__ << " The requested maxSpeed " << speed << " is less than 1");
      WARN_STREAM_NAMED("abdrive", __FUNCTION__ << " Behaviour not documented, so cowardly bailing out");
      return;
    }

  // Store value locally
  abd_speedLimit = speed;
  
  stringstream message;
  message << "ROBOT " << robotHandle << " drive_setMaxSpeed " << speed << "\n";

  // Send it out
  string result = serverConnection.sendMessageAndReturnReply(message.str());
}

void drive_goto(int distLeft, int distRight)
{
  stringstream message;
  message << "ROBOT " << robotHandle << " drive_goto " << distLeft << " " << distRight << "\n";

  // Send it out
  string result = serverConnection.sendMessageAndReturnReply(message.str());
}

void drive_getTicks(int *left, int *right)
{
  stringstream message;
  message << "ROBOT " << robotHandle << " drive_getTicks\n";
  string result = serverConnection.sendMessageAndReturnReply(message.str());
  int parsedResults = sscanf(result.c_str(), "OKAY TICKS %d %d", left, right);
  if (parsedResults != 2)
    {
      ERROR_STREAM_NAMED("abdrive", __FUNCTION__ << " error parsing response " << result);
      left = 0;
      right = 0;
    }
}

void drive_getTicksCalc(int *left, int *right)
{
  WARN_STREAM_NAMED("abdrive", __FUNCTION__ << " stub implementation; falling back to drive_getTicks");
  drive_getTicks(left, right);
}
