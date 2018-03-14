#include "CogManager.hpp"
#include "Console.hpp"

CogManager cogManager;

using namespace ::std;

CogManager::CogManager(size_t maxNumberOfCogs) : _cogThreadVector(maxNumberOfCogs), _cogAssignedVector(maxNumberOfCogs), _warningIssued(false)
{
}

void CogManager::stop()
{
  INFO_STREAM_NAMED("PropGCC", __FUNCTION__ << ": Joining all cog threads; might hang");
  for (size_t k = 0; k <  _cogThreadVector.size(); ++k)
    {
      if (_cogThreadVector[k] != nullptr)
        {
          INFO_STREAM_NAMED("PropGCC", __FUNCTION__ << ": Joining the thread for cog " << k);
          _cogThreadVector[k]->join();
        }
    }
}

void CogManager::start()
{
  lock_guard<mutex> cogGuard(_cogLock);
  INFO_STREAM_NAMED("PropGCC", __FUNCTION__ << ": Initialised with " << _cogThreadVector.size() << " available cogs");
  for (size_t k = 0; k <  _cogThreadVector.size(); ++k)
    {
      _cogThreadVector[k] = nullptr;
      _cogAssignedVector[k] = false;
    }
}

int CogManager::allocateEmptyCog()
{
  lock_guard<mutex> cogGuard(_cogLock);

  DEBUG_STREAM_NAMED("PropGCC", __FUNCTION__ << ": Invoked");
  
  for (size_t k = 0; k < _cogThreadVector.size(); ++k)
    {
      if (_cogAssignedVector[k] == false)
        {
          _cogAssignedVector[k] = true;
          return k;
        }
    }
  return -1;
}

int CogManager::startCog(void (*func)(void *), void *par)
{
  lock_guard<mutex> cogGuard(_cogLock);

  for (size_t k = 0; k < _cogThreadVector.size(); ++k)
    {
      if (_cogAssignedVector[k] == false)
        {
          _cogThreadVector[k] = ThreadPtr(new thread(func, par));
          _cogAssignedVector[k] = true;
          return k;
        }
    }
  return -1;
}

void CogManager::stopCog(int cogid)
{
  lock_guard<mutex> cogGuard(_cogLock);
  if ((cogid < 0) || (cogid > _cogThreadVector.size()))
    {
      ERROR_STREAM_NAMED("PropGCC", __FUNCTION__ << ": Illegal cogid " << cogid << "; the permitted range  is 0-" << _cogThreadVector.size());
      return;
    }

  if (_cogAssignedVector[cogid] == false)
    {
      WARN_STREAM_NAMED("PropGCC", __FUNCTION__ << ": Attempt to stop cog cogid " << cogid << " which is currently not assigned");
      return;
    }
  
  if (_cogThreadVector[cogid] != nullptr)
    {
      _cogThreadVector[cogid]->join();
    }
  
  _cogAssignedVector[cogid] = false;
}
