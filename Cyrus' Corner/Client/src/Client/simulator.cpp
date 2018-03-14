#include "simulator.h"
#include "Console.hpp"
#include "launcher.hpp"

#include <sstream>
#include <cstdio>
#include <cmath>

using namespace ::std;

int simulator_getPose(double* x, double* y, double* theta)
{
  stringstream message;
  message << "ROBOT " << robotHandle << " getPose\n";
  
  // Send it out
  string result = serverConnection.sendMessageAndReturnReply(message.str());

  int parsedResults = sscanf(result.c_str(), "OKAY pose %lf %lf %lf", x, y, theta);
  if (parsedResults != 3)
    {
      ERROR_STREAM_NAMED("simulator", __FUNCTION__ << " error parsing response " << result);
      x = 0;
      y = 0;
      theta = 0;
      return -1;
    }
  return 0;
}

void simulator_setEncoderTicksPerRevolution(int left, int right)
{
  // Validate the arguments
  if ((left < 0) || (right < 0))
    {
      ERROR_STREAM_NAMED("simulator", __FUNCTION__ << ": attempt to set to " << left << ", " << right);
      ERROR_STREAM_NAMED("simulator", __FUNCTION__ << ": the values must be non-negative ");
      return;
    }
  
  stringstream message;
  message << "ROBOT " << robotHandle << " setEncoderTicksPerRevolution " << left << " " << right << "\n";

  serverConnection.sendMessageAndReturnReply(message.str());
}

int simulator_getEncoderTicksPerRevolution(int* left, int* right)
{
  stringstream message;
  message << "ROBOT " << robotHandle << " getEncoderTicksPerRevolution\n";
  
  // Send it out
  string result = serverConnection.sendMessageAndReturnReply(message.str());

  double leftTick, rightTick;
  
  int parsedResults = sscanf(result.c_str(), "OKAY encoderTicksPerRevolution %lf %lf", &leftTick, &rightTick);
  if (parsedResults != 2)
    {
      ERROR_STREAM_NAMED("simulator", __FUNCTION__ << " error parsing response " << result);
      left = 0;
      right = 0;
      return -1;
    }

  *left = int(leftTick);
  *right = int(rightTick);
  
  return 0;
}

void simulator_startNewSmokeTrail()
{
  stringstream message;
  message << "ROBOT " << robotHandle << " startNewSmokeTrail\n";
  
  // Send it out
  string result = serverConnection.sendMessageAndReturnReply(message.str());
}


void simulator_stopSmokeTrail()
{
  stringstream message;
  message << "ROBOT " << robotHandle << " stopSmokeTrail\n";
  
  // Send it out
  string result = serverConnection.sendMessageAndReturnReply(message.str());
}


void simulator_removeAllSmokeTrails()
{
  stringstream message;
  message << "ROBOT " << robotHandle << " removeAllSmokeTrails\n";
  
  // Send it out
  string result = serverConnection.sendMessageAndReturnReply(message.str());
}

void simulator_showRobotConfiguration()
{
  stringstream message;
  message << "ROBOT " << robotHandle << " getConfiguration\n";

  // Send it out
  string result = serverConnection.sendMessageAndReturnReply(message.str());

  // Show the results
  INFO_STREAM_NAMED("simulator", __FUNCTION__ << " The returned robot configuration is:\n" << result);
}
