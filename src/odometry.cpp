#include "vex.h" // vex standard library
#include <cmath>

// global odom vars
double globalX;
double globalY;
double globalTheta;
// declare everything used in odom func
double _left;
double _right;
double back;
double header;
double leftChange;
double rightChange;
double backChange;
double headerChange;
double leftChangeRad;
double rightChangeRad;
double backChangeRad;
double leftDistance;
double rightDistance;
double backDistance;
double sumDistance;
double yDistance;
double localXOffset;
double localYOffset;
double scaledX;
double scaledY;
double offset;
double lastLeft;
double lastRight;
double lastBack;
double lastHeader;

#define pi 3.14159265359

/** 
 * Updates global position variables based on inertial and encoder readings. Uses 3-encoder system.
 */
void odom() {
  // store the current encoder and inertial readings
  _left = encoderL.rotation(deg);
  _right = encoderR.rotation(deg);
  back = encoderB.rotation(deg);
  header = _inertial.heading(rotationUnits::deg) * pi / 180.0;
  
  // calculate the change in all the variables since the last cycle
  headerChange = header - lastHeader;

  // convert the encoder rotation from degrees to radians
  leftChangeRad = _left - lastLeft * pi / 180.0;
  rightChangeRad = _right - lastRight * pi / 180.0;
  backChangeRad = back - lastBack * pi / 180.0;

  // calculate the linear distance of the wheel
  leftDistance = ODOM_WHEEL_DIAMETER / 2.0 * leftChangeRad;
  rightDistance = ODOM_WHEEL_DIAMETER / 2.0 * rightChangeRad;
  backDistance = ODOM_WHEEL_DIAMETER / 2.0 * backChangeRad;
  sumDistance = leftDistance + rightDistance;
  yDistance = sumDistance / 2.0;

  // update the 'last' values
  lastLeft = _left;
  lastRight = _right;
  lastBack = back;
  lastHeader = header;

  offset = 2 * sin(headerChange / 2.0);
  localXOffset = offset * (backDistance / headerChange + ODOM_BACK_DISTANCE);
  localYOffset = offset * (yDistance / headerChange + ODOM_RIGHT_DISTANCE);

  // rotational matrix to get the offsets back to global offsets
  scaledX = localXOffset * cos(header) + localYOffset * sin(header);
  scaledY = localYOffset * cos(header) - localXOffset * sin(header);

  // update global values
  globalX += scaledX;
  globalY += scaledY;
}

void odomInit() {
  _inertial.calibrate();

  while (_inertial.isCalibrating()) {
    task::sleep(20);
  };
  _inertial.resetHeading();
}