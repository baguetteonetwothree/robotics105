#ifndef __COG_MANAGER_HPP__
#define __COG_MANAGER_HPP__

#include <thread>
#include <memory>
#include <vector>
#include <mutex>

typedef std::shared_ptr<std::thread> ThreadPtr;
typedef std::vector<ThreadPtr> ThreadPtrVector;
typedef std::vector<bool> BoolVector;

// This class represents an approximation to a cog. It is
class Cog
{
};

// This class wraps up managing the cogs. These are approximated as a
// fixed-sized threadpool with up to eight threads.

class CogManager
{
public:
  CogManager(size_t maxNumberOfCogs = 8);

  void start();

  void stop();
  

  int allocateEmptyCog();

  int startCog(void (*func)(void *), void *par);

  void stopCog(int cogid);

private:
  // List of the threads
  ThreadPtrVector _cogThreadVector;
  
  // Boolean to show if a cog has been allocated
  BoolVector _cogAssignedVector;

  // Mutex for managing access
  std::mutex _cogLock;

  // Flag shows if the warning was issued
  bool _warningIssued;
};

extern CogManager cogManager;

#endif // __COG_MANAGER_HPP__
