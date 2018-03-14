#include "serial.h"

#include "Console.hpp"

extern "C" {
	extern HUBDATA terminal *dport_ptr;
}

void simpleterm_close()
{
  WARN_STREAM_NAMED("libsimpletool", __FUNCTION__ << ": Stub implementation; the terminal is not closed");
}

terminal *simpleterm_reopen(int rxpin, int txpin, int mode, int baud)
{
  WARN_STREAM_NAMED("libsimpletool", __FUNCTION__ << ": Stub implementation; nothing to do with the terminal");
  return dport_ptr;
}
