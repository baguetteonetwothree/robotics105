#include "servo.h"

#include "Console.hpp"

int servo_angle(int pin, int degreeTenths)
{
  WARN_STREAM_NAMED("libservo", __FUNCTION__ << ": Stub implementation called with pin=" << pin
		    << "; degreeTenths=" << degreeTenths);
  return -1;
}

int servo_speed(int pin, int speed)
{
  WARN_STREAM_NAMED("libservo", __FUNCTION__ << ": Stub implementation called with pin=" << pin
		    << "; speed=" << speed);
  return -1;
}

int servo_setramp(int pin, int stepSize)
{
  WARN_STREAM_NAMED("libservo", __FUNCTION__ << ": Stub implementation called with pin=" << pin
		    << "; stepSize=" << stepSize);
  return -4;
}

int servo_set(int pin, int time)
{
  WARN_STREAM_NAMED("libservo", __FUNCTION__ << ": Stub implementation called with pin=" << pin
		    << "; time=" << time);
  return -1;
}

int servo_get(int pin)
{
  WARN_STREAM_NAMED("libservo", __FUNCTION__ << ": Stub implementation called with pin=" << pin);
  return 0;
}

int servo_disable(int pin)
{
  WARN_STREAM_NAMED("libservo", __FUNCTION__ << ": Stub implementation called with pin=" << pin);
  return -1;
}

void servo_stop(void)
{
  WARN_STREAM_NAMED("libservo", __FUNCTION__ << ": Stub implementation");
}
