#include "Console.hpp"

#include "stacktest.h"

int *cog_runStackTest(void (*function)(void *par), int stacksize)
{
  WARN_STREAM_NAMED("libstacktest", __FUNCTION__ << ": Stub implementation");
  return NULL;
}

int cog_endStackTest(int *coginfo)
{
  WARN_STREAM_NAMED("libstacktest", __FUNCTION__ << ": Stub implementation");
  return 0;
}

int cogstart_stackTest(void (*func)(void *), void *par, void *stack, size_t stacksize)
{
  WARN_STREAM_NAMED("libstacktest", __FUNCTION__ << ": Stub implementation");
  return -1;
}

int cogstop_stackTest(int cog, void *stack)
{
  WARN_STREAM_NAMED("libstacktest", __FUNCTION__ << ": Stub implementation");
  return 0;
}
