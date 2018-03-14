#ifdef _MSC_VER
#define NOMINMAX
#endif

#include "simpletools.h"                      // simpletools function prototypes

// This file batches together dac_ctr, freqout and input calls. The
// reason is that all three are used in tandem to ping the IR
// sensor. It is inefficient to map these out separately into a
// sequence of separate calls to the simulator. Instead, it caches the
// results and makes a single range query. Note that the timing is
// slightly off - each call should take msTime ms to complete.

#include <sstream>
#include <limits>

#include "Console.hpp"
#include "launcher.hpp"

#undef EXPERIMENTAL_BATCH_METHOD

using namespace ::std;

// Cache settings

static int lastInputPin = -1;
static int lastOutputPin = -1;
static int lastChannel = -1;
static int lastDACPin = -1;
static int lastDACVal = -1;
static int lastFrequency = -1;
static long lastCNT = -1000 * 1000 * 1000;

// Should we get an IR reading from the simulator?
static bool pingTheSimulator = false;

// The last range measurement from the simulator
static int lastResultFromTheSimulator = -1;
static double lastRangeMeasurementFromTheSimulator = -1;

void dac_ctr_stop()
{
  WARN_STREAM_NAMED("abdrive", __FUNCTION__ << " stub implementation");
}

void dac_ctr(int pin, int channel, int dacVal)
{
  // Force pinging the server if any of the pin settings have changed
  pingTheSimulator = (pin != lastDACPin)  || (channel != lastChannel);

  lastDACPin = pin;
  lastChannel = channel;
  lastDACVal = dacVal;
  
#ifndef EXPERIMENTAL_BATCH_METHOD
  stringstream message;
  message << "ROBOT " << robotHandle << " dac_ctr " << pin << " " << channel << " " << dacVal << "\n";
  
  // Send it out
  string result = serverConnection.sendMessageAndReturnReply(message.str());
#endif
}

void freqout(int pin, int msTime, int frequency)
{
  // Force pinging the server if any of the pin settings have changed
  pingTheSimulator |= (pin != lastOutputPin) || (frequency != lastFrequency);

#ifndef EXPERIMENTAL_BATCH_METHOD
  stringstream message;
  message << "ROBOT " << robotHandle << " freqout " << pin << " " << msTime << " " << frequency << "\n";
  
  // Send it out
  string result = serverConnection.sendMessageAndReturnReply(message.str());
#endif
}

int input(int pin)
{
#ifdef EXPERIMENTAL_BATCH_METHOD
  // Force pinging the server if any of the pin settings have changed, or it's been more than 20ms since the last ping
  pingTheSimulator |= (pin != lastInputPin) || (CNT - lastCNT > 20 * 1000 * 1000);
  
  if (pingTheSimulator == true)
    {
      lastCNT = CNT;

      // Check the various settings to make sure a valid configuration was chosen
      bool leftIRSensor = (lastDACPin == 26) && (lastChannel == 0) && (lastOutputPin == 11) && (lastInputPin == 10);
      bool rightIRSensor = (lastDACPin == 27) && (lastChannel == 1) && (lastOutputPin == 1) && (lastInputPin == 2);
      bool validPinConfiguration = leftIRSensor | rightIRSensor;

      if (validPinConfiguration == false)
        {
          ERROR_STREAM_NAMED("libsimpletools", __FUNCTION__ << " The configuration does not match a valid configuration for pingin the IR sensor");
          ERROR_STREAM_NAMED("libsimpletools", __FUNCTION__ << " The specified configuration is ...");
          ERROR_STREAM_NAMED("libsimpletools", __FUNCTION__ << " Known configurations are ...");
          
          // Generate error and return
          return 1;
        }

      // Shape the message to the server
      stringstream message;
      message << "ROBOT " << robotHandle << " measureIRRange " << rightIRSensor << "\n";

      // Send it out
      string result = serverConnection.sendMessageAndReturnReply(message.str());

      // Parse the results
      if (sscanf(result.c_str(), "OKAY %lf", &lastRangeMeasurementFromTheSimulator) != 1)
        {
          ERROR_STREAM_NAMED("libsimpletools", __FUNCTION__ << " Could not parse distance from " << result);
          lastRangeMeasurementFromTheSimulator = numeric_limits<double>::max();
        }
    }

#endif
  
#ifndef EXPERIMENTAL_BATCH_METHOD
    stringstream message;
  message << "ROBOT " << robotHandle << " input " << pin << "\n";
  
  // Send it out
  string result = serverConnection.sendMessageAndReturnReply(message.str());
  // Parse the results
  if (sscanf(result.c_str(), "OKAY %d %lf", &lastResultFromTheSimulator, &lastRangeMeasurementFromTheSimulator) != 2)
    {
      ERROR_STREAM_NAMED("libsimpletools", __FUNCTION__ << " Could not parse distance from " << result);
      lastRangeMeasurementFromTheSimulator = numeric_limits<double>::max();
    }

#endif

  //DEBUG_STREAM_NAMED("libsimpletools", __FUNCTION__ << ": lastResultFromTheSimulator=" << lastResultFromTheSimulator
  //                   << "; lastRangeMeasurementFromTheSimulator =  " << lastRangeMeasurementFromTheSimulator);
  
  // Based on the lastDACVal, decide if we return a 0 or a 1; very crude approach!
  return lastResultFromTheSimulator;
}
