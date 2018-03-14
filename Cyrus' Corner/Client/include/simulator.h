#ifndef __SIMULATOR_H__
#define __SIMULATOR_H__

// This header file provides some simulator-specific methods for
// accessing and setting things like the robot state. The names are
// deliberately different to show that these are not "normal" commands
// and are not available on the regular robot platform.

#if defined(__cplusplus)
extern "C" {
#endif

  // Get the pose (position, orientation) of the centre of the robot
  // in world coordinates. (Note that the centre is NOT the midpoint
  // between the two front wheels.)
  //
  // The coordinate system is a right handed one: the origin is in the
  // bottom left corner. +ve x points to the right, +y points up and
  // positive theta is in a clockwise direction. The transformation
  // which this encodes is "rotate by an angle theta and then
  // translate by x and y".

  // Units are mm and radians.

  // Return value is 0 on success, -1 on failure.
  
  int simulator_getPose(double* x, double* y, double* theta);

  // For each complete revolution from each wheel, how many encoder
  // ticks are computed? Note that setting this immediately causes the
  // simulator to internally change these values, even if an operation
  // (e.g., drive_goto) is under way. Therefore, only apply this when
  // the robot is stationary, probably at the very start of the
  // program.
  void simulator_setEncoderTicksPerRevolution(int left, int right);

  // Return the encoder ticks.

  // Return value is 0 on success, -1 on failure.
  
  int simulator_getEncoderTicksPerRevolution(int* left, int* right);

  // Start the smoke trail going
  void simulator_startNewSmokeTrail();

  // Stop the current smoke trail
  void simulator_stopSmokeTrail();
  
  // Stop the smoke trail
  void simulator_removeAllSmokeTrails();

  // Show the robot configuration as a string
  void simulator_showRobotConfiguration();  
  
#if defined(__cplusplus)
}
#endif

#endif // __SIMULATOR_H__
