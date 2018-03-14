// This file defines a static instance

#include "ServerConnection.hpp"
#include "Console.hpp"

#include <cstring>
#include <sstream>
#include <cinttypes>

#include "simpletools.h"

#define READBUFLEN 4096

using namespace ::std;

// Useful helper from http://stackoverflow.com/questions/7755719/check-if-string-starts-with-another-string-find-or-compare

static bool starts_with(const string& s1, const string& s2)
{
    return s2.size() <= s1.size() && s1.compare(0, s2.size(), s2) == 0;
}

// From http://stackoverflow.com/questions/17023302/find-c-nth-occurrence-of-a-substring-from-a-string

static size_t find_Nth(const std::string & str, unsigned N, const std::string & find)
{
  if ( 0==N ) { return std::string::npos; }
  size_t pos,from=0;
  unsigned i=0;
  while ( i<N ) {
    pos=str.find(find,from);
    if ( std::string::npos == pos ) { break; }
    from = pos + 1; // from = pos + find.size();
    ++i;
  }
  return pos;
}

ServerConnection::ServerConnection()
{
}

ServerConnection::~ServerConnection()
{
}

bool ServerConnection::open(const std::string& address, const unsigned short port)
{
  lock_guard<mutex> messageGuard(_messageLock);

  try
    {
      _serverSocket.connect(address, port);
    }
  catch(...)
    {
      FATAL_STREAM_NAMED("ServerConnection", "Could not open connection with the simulator - is it running?");
      return false;
    }
  return true;
}


void ServerConnection::resetServer()
{
  //DEBUG_STREAM_NAMED("ServerConnection", "Invoked");

  string message = "SIMULATOR reset\n";

  sendMessageAndReturnReply(message);
}

int ServerConnection::getRobotHandle(int id, const std::string& type)
{
  //DEBUG_STREAM_NAMED("ServerConnection", "Invoked to get a robot of ID " << id << " and type " << type);

  /* Construct the simulator message and check that it isn't too long*/
  stringstream command;
  command << "SIMULATOR getRobotHandle " << id << " " << type << "\n";

  string results = sendMessageAndReturnReply(command.str());
  
  // Scan for the ID
  int robotHandle;

  if (sscanf(results.c_str(), "OKAY %d", &robotHandle) == 0)
    {
      FATAL_STREAM_NAMED("ServerConnection", "Could not get the robot handle; the reply is " << results);
      return -1;
    }

  INFO_STREAM_NAMED("ServerConnection", "The robot handle is " << robotHandle);
  
  return robotHandle;
}

string ServerConnection::sendMessageAndReturnReply(const string& message)
{
  lock_guard<mutex> messageGuard(_messageLock);

  //DEBUG_STREAM_NAMED("ServerConnection", "Sending message " << message);

  try
    {
      _serverSocket.send(message.c_str(), message.length());
      char buffer[READBUFLEN];

      // First the reply
      int bytes = _serverSocket.recv(buffer, READBUFLEN-1);
      
      if (bytes <= 0)
        {
          ERROR_STREAM_NAMED("ServerConnection", "Error receiving reply");
          return "ERR: FAIL";
        }

      //DEBUG_STREAM_NAMED("ServerConnection", "Received " << bytes);

      string fullResponse(buffer, 0, size_t(bytes));

      //DEBUG_STREAM_NAMED("ServerConnection", "Received " << fullResponse);

      // Parse the time step
      uint64_t newTime;

      if (sscanf(fullResponse.c_str(), "TIMESYNC %" SCNi64, &newTime) != 1)
        {
          FATAL_STREAM_NAMED("ServerConnection", "Error parsing the timesync message; the received message is " << fullResponse);
          return "";
        }

      // Set the time to the timesync value; trying to set this in such a way to minimise the risk of numerical overflow
      _CNT = uint64_t(double(CLKFREQ * 1e-9) * double(newTime));

      //DEBUG_STREAM_NAMED("ServerConnection", "Setting the time count to " << _CNT << " (" << (newTime * 1e-9) << "s)");

      // The reply string is the rest of the message after the timesync
      size_t idx = find_Nth(fullResponse, 2, " ");

      if (idx == string::npos)
        {
          ERROR_STREAM_NAMED("ServerConnection", "The reply only consisted of the timesync");
          return "ERR: FAIL";
        }

      string reply = fullResponse.substr(idx + 1);

      // Check the message and print standard warnings
      if (starts_with(reply, "OKAY"))
        {
          //DEBUG_STREAM_NAMED("ServerConnection", "Received reply " << reply);
        }
      else if (starts_with(reply, "WARN"))
        {
          WARN_STREAM_NAMED("ServerConnection", "Warning with sending message " << message);
          WARN_STREAM_NAMED("ServerConnection", "Received warning reply " << reply);
        }
      else if (starts_with(reply, "ERR"))
        {
          ERROR_STREAM_NAMED("ServerConnection", "Error with sending message " << message);
          ERROR_STREAM_NAMED("ServerConnection", "Received reply " << reply);
        }
      else if (starts_with(reply, "FATAL"))
        {
          FATAL_STREAM_NAMED("ServerConnection", "Fatal with sending message " << message);
          FATAL_STREAM_NAMED("ServerConnection", "Received fatal reply " << reply);
        }
      
      return reply;
    }
  catch(...)
    {
      ERROR_STREAM_NAMED("ServerConnection", "Exception thrown");
      return "";
    }
}
