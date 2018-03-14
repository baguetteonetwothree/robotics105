#include "simpletools.h"                      // simpletools function prototypes

#include "Console.hpp"


void set_io_timeout(long clockTicks)          // setTimeout function definition
{
  WARN_STREAM_NAMED("libsimpletools", __FUNCTION__ << ": Invoked; existing = " << st_timeout << "; new = " << clockTicks);
  st_timeout = clockTicks;
}

