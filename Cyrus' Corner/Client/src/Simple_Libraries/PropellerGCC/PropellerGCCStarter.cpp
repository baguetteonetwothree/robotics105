// This C++ file is used to call startup routines for the library. The
// trick is to create a static object.

#include "PropellerGCCStarter.hpp"
#include "CogManager.hpp"
#include "simpletools.h"

PropellerGCCStarter::PropellerGCCStarter()
{
  cogManager.start();
};


PropellerGCCStarter::~PropellerGCCStarter()
{
  cogManager.stop();
};
