#include "simpletools.h"

#include "Console.hpp"
#include "launcher.hpp"

// The epoch time
static uint64_t epoch;

// The time offset at the epoch time
static uint64_t offset;

static void syncTimeWithServer()
{
  // Ping the simulator
  serverConnection.sendMessageAndReturnReply("SIMULATOR getTimeInNanos\n");
}

void epochTimeSetup()
{
  //DEBUG_STREAM_NAMED("libsimpletools", __FUNCTION__ << ": epoch set up to CNT = " << CNT);
  epoch = CNT;
  offset = 0;
}

int simpletools_gettimeofday(timeval *tv, void *unused)
{
  // First coordinate with the server to make sure we have the most current time
  syncTimeWithServer();
  
  // Convert the timer ticks into seconds after the epoch
  double deltaT = (1e-6 * (offset + CNT - epoch)) / (st_usTicks);

  //DEBUG_STREAM_NAMED("libsimpletools", __FUNCTION__ << ": offset + CNT - epoch = " << offset + CNT - epoch);
  //DEBUG_STREAM_NAMED("libsimpletools", __FUNCTION__ << ": deltaT = " << deltaT);
  
  // Cast to extract what we need
  tv->tv_sec = int(deltaT);
  tv->tv_usec = int(1e6*(deltaT - tv->tv_sec));
  return 0;
}

int simpletools_settimeofday(const struct timeval *tv, const void *unused)
{
  // First coordinate with the server to make sure we have the most current time
  syncTimeWithServer();

  // Set the various values
  epoch = CNT;
  offset = (1000000L * tv->tv_sec + tv->tv_usec) * st_usTicks;

  //DEBUG_STREAM_NAMED("libsimpletools", __FUNCTION__ << ": epoch = " << epoch << "; offset = " << offset);
  
  
  return 0;
}
