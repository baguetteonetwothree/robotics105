#include "simpletools.h"                      // simpletools function prototypes

#include <sstream>

#include "Console.hpp"
#include "launcher.hpp"

using namespace ::std;

void pause(int time)
{
  stringstream message;

  message << "SIMULATOR pauseClientInNanos " << (uint64_t(time) * uint64_t(st_pauseTicks) * 1000000L) / uint64_t(ms) << "\n";
  
  // Send it out
  string result = serverConnection.sendMessageAndReturnReply(message.str());
}
