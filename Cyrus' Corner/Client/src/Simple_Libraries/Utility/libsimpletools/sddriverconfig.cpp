#include "simpletools.h"

#include "Console.hpp"

static bool sdMounted = false;

// Remove our #define to avoid infinite loops!
#undef fopen

// The correct values for the pins; from http://learn.parallax.com/propeller-c-simple-devices/sd-card-data
static const int DO = 22, CLK = 23, DI = 24, CS = 25; 

int sd_mount(int doPin, int clkPin, int diPin, int csPin)
{
  // If the values are correct, mount okay
  if ((doPin == DO) && (clkPin == CLK) && (diPin == DI) && (csPin == CS))
    {
      INFO_STREAM_NAMED("libsimpletools", __FUNCTION__ << ": Pseudo-SD card mounted; file I/O enabled");
      sdMounted = true;
      return 0;
    }

  ERROR_STREAM_NAMED("libsimpletools", __FUNCTION__ << ": Wrong parameter values sent in; pseudo-SD card not mounted");
  ERROR_STREAM_NAMED("libsimpletools", __FUNCTION__ << ": The passed in parameters were " << doPin << " " << clkPin << " " << diPin << " " << csPin);
  ERROR_STREAM_NAMED("libsimpletools", __FUNCTION__ << ": The correct parameters are " << DO << " " << CLK << " " << DI << " " << CS);
  return 6;
}

// If the SD card is not mounted, file I/O fails. Therefore, simply return NULL

FILE* simpletools_fopen(const char * filename, const char * mode)
{
  if (sdMounted == false)
    {
      ERROR_STREAM_NAMED("libsimpletools", __FUNCTION__ << " Attempt to open file " << filename << " with mode " << mode);
      ERROR_STREAM_NAMED("libsimpletools", __FUNCTION__ << " The pseudo-SD card has not been mounted; the open will fail");
      return NULL;
    }

  return fopen(filename, mode);
}

      
