#ifndef __SERVER_CONNECTION_HPP__
#define __SERVER_CONNECTION_HPP__

#include <thread>
#include <string>
#include <mutex>
#include <memory>
#include <list>

#include "PracticalSocket.hpp"

class ServerConnection
{
public:

  ServerConnection();

  bool open(const std::string& address, const unsigned short port);

  void resetServer();

  int getRobotHandle(int id, const std::string& type);

  string sendMessageAndReturnReply(const std::string& message);
  
  virtual ~ServerConnection();

private:

  // The socket
  TCPSocket _serverSocket;

  // Messages are sent using this
  std::mutex _messageLock;
};


#endif // __SERVER_CONNECTION_HPP__
