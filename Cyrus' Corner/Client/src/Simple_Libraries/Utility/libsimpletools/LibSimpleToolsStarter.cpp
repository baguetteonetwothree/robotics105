// This C++ file is used to call startup routines for the library. The
// trick is to create a static object.

#include "LibSimpleToolsStarter.hpp"
#include "Console.hpp"
#include "simpletools.h"

extern "C"
{
  void timeTicksSetup();
}

extern void epochTimeSetup();
extern void eepromStart();

LibSimpleToolsStarter::LibSimpleToolsStarter()
{
  timeTicksSetup();
  INFO_STREAM_NAMED("libsimpletools", "Time ticks setup");
  DEBUG_STREAM_NAMED("libsimpletools", "ms=" << ms);
  DEBUG_STREAM_NAMED("libsimpletools", "us=" << us);
  DEBUG_STREAM_NAMED("libsimpletools", "st_iodt=" << st_iodt);
  DEBUG_STREAM_NAMED("libsimpletools", "st_pauseTicks=" << st_pauseTicks);
  DEBUG_STREAM_NAMED("libsimpletools", "st_timeout=" << st_timeout);

  // Setup the epoch for get / set time of day
  epochTimeSetup();
  
  // Now start the EEPROM manager
   eepromStart();
};
