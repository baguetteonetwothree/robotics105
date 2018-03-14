#include "propeller.h"

#include "propeller_builtins.h"

#include "Console.hpp"

void __builtin_propeller_clkset(int mode)
{
  WARN_STREAM_NAMED("propeller", __FUNCTION__ << " stub implementation");
}

int __builtin_propeller_cogid()
{
  WARN_STREAM_NAMED("propeller", __FUNCTION__ << " stub implementation");
  return 0;
}

int __builtin_propeller_coginit(int id)
{
  WARN_STREAM_NAMED("propeller", __FUNCTION__ << " stub implementation");
  return 1;
}
  
void __builtin_propeller_cogstop(int a)
{
  WARN_STREAM_NAMED("propeller", __FUNCTION__ << " stub implementation");
}

void __builtin_propeller_lockret(int lockid)
{
  WARN_STREAM_NAMED("propeller", __FUNCTION__ << " stub implementation");
}


void __builtin_propeller_lockset(int lockid)
{
  WARN_STREAM_NAMED("propeller", __FUNCTION__ << " stub implementation");
}


void __builtin_propeller_lockclr(int lockid)
{
  WARN_STREAM_NAMED("propeller", __FUNCTION__ << " stub implementation");
}


int __builtin_propeller_waitcnt(int a, int b)
{
  WARN_STREAM_NAMED("propeller", __FUNCTION__ << "(" << a << "," << b << ") stub implementation");
  return 0;
}


void __builtin_propeller_waitpeq(int state, int mask)
{
  WARN_STREAM_NAMED("propeller", __FUNCTION__ << " stub implementation");
}


void __builtin_propeller_waitpne(int state, int mask)
{
  WARN_STREAM_NAMED("propeller", __FUNCTION__ << " stub implementation");
}


void __builtin_propeller_waitvid(long colors, int pixels)
{
  WARN_STREAM_NAMED("propeller", __FUNCTION__ << " stub implementation");
}
