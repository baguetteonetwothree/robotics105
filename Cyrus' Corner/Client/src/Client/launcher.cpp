// This does the real work for starting up the interface to the
// simulator. It opens the connection to the server and requests the
// construction of an ActivityBot. The instance for this is stored for
// all later ActivityBot calls.

#include "launcher.hpp"
#include "ServerConnection.hpp"
#include "Console.hpp"
#include "abdrive.h"
#include "simulator.h"
#include <cstdlib>

// simpletools.h redefines main to allow the routine below to silently
// run. Unfortunately, we then have to revert this to get this bit of
// code to run!
#undef main

// The steaming pile which is MSVC doesn't define any POSIX standard stuff
#ifdef _MSC_VER
# define EX_OK      0   /* successful termination */
# define EX_NOHOST  68  /* host name unknown */
# define EX_UNAVAILABLE 69  /* service unavailable */
#else
#include <sysexits.h>
#endif

#include "../Simple_Libraries/PropellerGCC/PropellerGCCStarter.hpp"
#include "../Simple_Libraries/Utility/libsimpletools/LibSimpleToolsStarter.hpp"
#include "../Simple_Libraries/TextDevices/libsimpletext/LibSimpleTextStarter.hpp"

using namespace ::std;

// The program main is renamed to this
extern "C"
{
  extern int activityBotCodeMain(int argc, const char* argv[]);
};

// The server connection
ServerConnection serverConnection;

// The handle for the robot
int robotHandle;

// Clean shutdown routine
static void stopRobotOnExit()
{
  drive_close();
}

int main(int argc, const char* argv[])
{
  // These objects are responsible for starting up the different
  // libraries; when they are destructed at the end, they shut the
  // libraries back down again
  PropellerGCCStarter propellerGCCStarter;
  LibSimpleToolsStarter libSimpleToolsStarter;
  LibSimpleTextStarter libSimpleTextStarter;
  
  // Connect to the server
  if (serverConnection.open("127.0.0.1", 30000) == false)
    {
      return EX_NOHOST;
    }

  // Register handler for clean shutdown on exit
  atexit(stopRobotOnExit);

  // Reset the simulation server. This does stuff like puts the robot
  // back in its default position.
  serverConnection.resetServer();
  
  // Get the activity bot
  robotHandle = serverConnection.getRobotHandle(0, "ActivityBot");

  if (robotHandle < 0)
    {
      FATAL_STREAM_NAMED("launcher", "Failed to get a handle to a robot instance in the simulator");
      return EX_UNAVAILABLE;
    }

  // Show the robot configuration
  simulator_showRobotConfiguration();
  
  // Run the main code
  int returnValue = activityBotCodeMain(argc, argv);

  return returnValue;
}
