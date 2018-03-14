#include "cog.h"
#include "propeller.h"
#include "Console.hpp"

#include "CogManager.hpp"

// From activityboard.cfg 
uint64_t _clkfreq = uint64_t(80000000);

// From activityboard.cfg and https://lamestation.atlassian.net/wiki/display/SPIN/_CLKMODE
unsigned char _clkmode = 111;

// Various variables

uint64_t _PAR = 0;
uint64_t _CNT = 0;
uint64_t _INA = 0;
uint64_t _INB = 0;
uint64_t _OUTA = 0;
uint64_t _OUTB = 0;
uint64_t _DIRA = 0;
uint64_t _DIRB = 0;
uint64_t _CTRA = 0;
uint64_t _CTRB = 0;
uint64_t _FRQA = 0;
uint64_t _FRQB = 0;
uint64_t _PHSA = 0;
uint64_t _PHSB = 0;
uint64_t _VCFG = 0;
uint64_t _VSCL = 0;

int cogstart(void (*func)(void *), void *par, void *stack, size_t stacksize)
{
  INFO_STREAM_NAMED("PropellerGCC", __FUNCTION__ << ": Invoked");
  return cogManager.startCog(func, par);
}
