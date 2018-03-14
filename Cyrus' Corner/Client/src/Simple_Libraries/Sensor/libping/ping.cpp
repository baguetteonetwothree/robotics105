#ifdef _MSC_VER
#define NOMINMAX
#endif

#include "simpletools.h"
#include "ping.h"

#include <sstream>

#include "Console.hpp"
#include "launcher.hpp"
#include <limits>

using namespace ::std;

// 1cm = 10mm = 58 ping units

int ping(int pin)
{
  if (pin != 8)
    {
      WARN_STREAM_NAMED("libping", __FUNCTION__ << " Invalid pin; the supported value is 8 but the requested value is "
                         << pin);
    }
  
  stringstream message;

  // pin, ping length and timeout. From ping.c
  message << "ROBOT " << robotHandle << " ping " << pin << " " << (10 * st_iodt * uint64_t(1000)) / uint64_t(us)
    	  << " " << (st_timeout * uint64_t(1000)) / uint64_t(us) << "\n";

  
  // Send it out and get the reply
  string result = serverConnection.sendMessageAndReturnReply(message.str());

  int range;

  if (sscanf(result.c_str(), "OKAY %d", &range) != 1)
    {
      range = numeric_limits<int>::max();
    }
  
  return range;
}

int ping_cm(int pin)
{
  long tEcho = ping(pin);
  int cmDist = tEcho / 58;
  return cmDist;
}

int ping_inches(int pin) 
{
  long tEcho = ping(pin);
  int inDist = tEcho / 148;
  return inDist;
}
