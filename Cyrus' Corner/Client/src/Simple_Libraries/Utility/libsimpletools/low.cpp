#include "simpletools.h"                      // simpletools function prototypes

#include <sstream>

#include "Console.hpp"
#include "launcher.hpp"

using namespace ::std;

void low(int pin)                             // low function definition
{
  if ((pin < 0) || (pin > 31))
    {
      ERROR_STREAM_NAMED("libsimpletool", __FUNCTION__ << " The pin value " << pin
                         << " falls outside the supported range (0,31)");
      ERROR_STREAM_NAMED("libsimpetool", __FUNCTION__ << " Behaviour not documented, so cowardly bailing out");
      return;
    }

  stringstream message;
  message << "ROBOT " << robotHandle << " low " << pin << "\n";
  
  // Send it out
  string result = serverConnection.sendMessageAndReturnReply(message.str());
}
