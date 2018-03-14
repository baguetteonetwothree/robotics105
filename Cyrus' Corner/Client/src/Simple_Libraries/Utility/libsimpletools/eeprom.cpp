#include "simpletools.h"

#include "Console.hpp"

#include <cstring>

using namespace ::std;

static const size_t EEPROM_SIZE = 65536;

static char eeProm[EEPROM_SIZE];

void eepromStart()
{
  INFO_STREAM_NAMED("libsimpletool", __FUNCTION__ << ": Setting up EEPROM with " << EEPROM_SIZE << " bytes");
  WARN_STREAM_NAMED("libsimpletool", __FUNCTION__ << ": EEPROM is simulated using an in memory buffer and is not persistent");
  memset(&eeProm, 0, EEPROM_SIZE);
}

char ee_getByte(int addr)
{
  if ((addr < 0) || (addr > EEPROM_SIZE-1))
    {
      ERROR_STREAM_NAMED("libsimpletool", __FUNCTION__ << ": The addr " << addr << " is out of range; permitted values are 0 - "
                         << EEPROM_SIZE-1);
      return '\0';
    }
  return eeProm[addr];
}

float ee_getFloat32(int addr)
{
  if ((addr < 0) || (addr > EEPROM_SIZE-4))
    {
      ERROR_STREAM_NAMED("libsimpletool", __FUNCTION__ << ": The addr " << addr << " is out of range; permitted values are 0 - "
                         << EEPROM_SIZE-4);
      return '\0';
    }
  float fpVal;
  memcpy(&fpVal, eeProm+addr, 4);
  return fpVal;
}

int ee_getInt(int addr)
{
  if ((addr < 0) || (addr > EEPROM_SIZE-4))
    {
      ERROR_STREAM_NAMED("libsimpletool", __FUNCTION__ << ": The addr " << addr << " is out of range; permitted values are 0 - "
                         << EEPROM_SIZE-4);
      return '\0';
    }
  int val;
  memcpy(&val, eeProm+addr, 4);
  return val;
}

unsigned char* ee_get_str(unsigned char *s, int n, int addr)
{
  if ((n < 0) || (n > EEPROM_SIZE))
    {
      ERROR_STREAM_NAMED("libsimpletool", __FUNCTION__ << ": The length " << n << " is invalid; permitted values are 0 - "
                         << EEPROM_SIZE);
      return NULL;
    }
  
  if ((addr < 0) || (addr+n > EEPROM_SIZE))
    {
      ERROR_STREAM_NAMED("libsimpletool", __FUNCTION__ << ": The addr " << addr << " is out of range; permitted values are 0 - "
                         << EEPROM_SIZE-n);
      return NULL;
    }
  memcpy(s, eeProm + addr, n);
  return s;
}

void ee_putByte(unsigned char value, int addr)
{
  if ((addr < 0) || (addr > EEPROM_SIZE-1))
    {
      ERROR_STREAM_NAMED("libsimpletool", __FUNCTION__ << ": The addr " << addr << " is out of range; permitted values are 0 - "
                         << EEPROM_SIZE-1);
      return;
    }
  eeProm[addr] = value;
}

void ee_putFloat32(float fpVal, int addr)
{
  if ((addr < 0) || (addr > EEPROM_SIZE-4))
    {
      ERROR_STREAM_NAMED("libsimpletool", __FUNCTION__ << ": The addr " << addr << " is out of range; permitted values are 0 - "
                         << EEPROM_SIZE-4);
      return;
    }
  memcpy(eeProm+addr, &fpVal, 4);
}

void ee_putInt(int value, int addr)
{
  if ((addr < 0) || (addr > EEPROM_SIZE-4))
    {
      ERROR_STREAM_NAMED("libsimpletool", __FUNCTION__ << ": The addr " << addr << " is out of range; permitted values are 0 - "
                         << EEPROM_SIZE-4);
      return;
    }
  memcpy(eeProm+addr, &value, 4);
}

void ee_putStr(unsigned char *s, int n, int addr)
{
  if ((n < 0) || (n > EEPROM_SIZE))
    {
      ERROR_STREAM_NAMED("libsimpletool", __FUNCTION__ << ": The length " << n << " is invalid; permitted values are 0 - "
                         << EEPROM_SIZE);
      return;
    }
  
  if ((addr < 0) || (addr+n > EEPROM_SIZE))
    {
      ERROR_STREAM_NAMED("libsimpletool", __FUNCTION__ << ": The addr " << addr << " is out of range; permitted values are 0 - "
                         << EEPROM_SIZE-n);
      return;
    }
  memcpy(eeProm + addr, s, n);
}

