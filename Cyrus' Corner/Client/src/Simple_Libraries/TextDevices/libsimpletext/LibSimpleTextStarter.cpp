#include "simpletext.h"
#include "Console.hpp"

#include <cstdio>

// Create a shim for the simple text. This just pipes everything via stdio

#include "LibSimpleTextStarter.hpp"

extern "C"
{
  extern text_t *dport_ptr;

  static int stdioRxChar(text_struct *p)
  {
    return getc(stdin);
  }
  
  static int stdioTxChar(struct text_struct *p, int ch)
  {
    return putc(ch, stdout);
  }
}

LibSimpleTextStarter::LibSimpleTextStarter()
{
  dport_ptr = new terminal();
  dport_ptr->rxChar = &stdioRxChar;
  dport_ptr->txChar = &stdioTxChar;
  INFO_STREAM_NAMED("simpletext", "Started with stdio stubs for the simpleterm");
}
