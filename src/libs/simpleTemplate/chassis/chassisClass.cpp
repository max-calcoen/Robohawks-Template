#include "vex.h"
#include "libs/simpleTemplate/chassis/chassisClass.h"
#include <cmath>
#define e 2.71828182846
#define pi 3.14159265359

Chassis::Chassis(motor_group l, motor_group r, double WHEEL_DIAMETER, double kP,  double kI, double kD, double turnKP, double turnKI, double turnKD) :
  dt(l, r),
  WHEEL_DIAMETER(WHEEL_DIAMETER) 
{
  this->left = l;
  this->right = r;
  this->kP = kP;
  this->kI = kI;
  this->kD = kD;
  this->turnKP = turnKP;
  this->turnKI = turnKI;
  this->turnKD = turnKD;
}

void Chassis::setK(double kP, double kI, double kD) {
  this->kP = kP;
  this->kI = kI;
  this->kD = kD;
}

inline double TankChassis::_limit(double val, double min, double max) { return val < min ? min : (val > max ? max : val); }

void TankChassis::drive(directionType dir, double dist, double speed) {
  double revolutions = dist / (WHEEL_DIAMETER * pi);
  double degrees = revolutions * 360;

  left.resetRotation();
  right.resetRotation();

  double distanceL = left.rotation(rotationUnits::deg);
  double distanceR = right.rotation(rotationUnits::deg);

  double errorL = degrees - distanceL;
  double errorR = degrees - distanceL;

  double lastErrorL = errorL;
  double lastErrorR = errorR;

  double proportionalL;
  double proportionalR;

  double speedL;
  double speedR;

  double derivativeL;
  double derivativeR;

  double powerL;
  double powerR;

  const double ERROR_MARGIN_INCHES = 1;
  const double ERROR_MARGIN_DEGREES = ERROR_MARGIN_INCHES * 360 / (WHEEL_DIAMETER * pi);
  while (fabs(errorL) > ERROR_MARGIN_DEGREES || fabs(errorR) > ERROR_MARGIN_DEGREES) {
    distanceL = left.rotation(rotationUnits::deg);
    distanceR = right.rotation(rotationUnits::deg);

    errorL = degrees - distanceL;
    errorR = degrees - distanceL;

    proportionalL = errorL * kP;
    proportionalR = errorR * kP;

    speedL = lastErrorL - errorL;
    speedR = lastErrorR - errorR;

    derivativeL = -speedL * kD;
    derivativeR = -speedR * kD;

    lastErrorL = errorL;
    lastErrorR = errorR;

    
    powerL = _limit((proportionalL + derivativeL) * 0.6, speed * -1 , speed); //* .6
    powerR = _limit((proportionalR + derivativeR) * 0.6, speed * -1 , speed); //* .6
    left.setVelocity(powerL, percentUnits::pct);
    right.setVelocity(powerR, percentUnits::pct);
    vex::task::sleep(10);
  }
  dt.stop();
}

void TankChassis::drive(directionType dir, double dist, double speed, double kP, double kI, double kD) {
  double temp [3] = {this->kP, this->kI, this->kD};
  this->kP = kP;
  this->kI = kI;
  this->kD = kD;
  this->drive(dir, dist, speed);
  this->kP = temp[0];
  this->kI = temp[1];
  this->kD = temp[2];
}

void TankChassis::turnTo(double angle, double speed) {
  this->setStopping(vex::brakeType::coast);

  // set initial values
  double currHeading = 0;
  double error = angle - currHeading;

  // adjust angle for turning counter-clockwise
  error += (error < 180 && error > -180) ? 0 : (error < -180 ? 360 : -360);

  // margin of error for turn
  const double ERROR_MARGIN_DEGREES = 0.75;
  const double MAX_INTEGRAL = 25;
  while (fabs(error) >= ERROR_MARGIN_DEGREES) {
    currHeading = _inertial.heading();
    error = angle - currHeading;

    // adjust angle for turning counter-clockwise
    error += (error < 180 && error > -180) ? 0 : (error < -180 ? 360 : -360);
    
    double lastError = error;
    double speed = error - lastError;
    
    // calculate motor velocity
    // P
    double proportion = error * turnKP;
    // I
    double integral = _limit(error * turnKI, 0, MAX_INTEGRAL);
    // D
    double deriative = speed * turnKD;
    
    double power = _limit((proportion + integral + deriative), -speed, speed);
    right.setVelocity(power, percentUnits::pct);
    left.setVelocity(-power, percentUnits::pct);
    vex::task::sleep(10);
    right.stop();
    left.stop();
  }
  this->setStopping(vex::brakeType::brake);
}

inline double TankChassis::curve(double val) {
  const double CURVE_SCALE = 3.5;
  // https://www.desmos.com/calculator/dgnbjxnj2z
  // using reworked version of pilon's input scaling
  return (powf(e, -(CURVE_SCALE / 10)) + powf(e, (fabs(val) - 100) / 10) * (1 - powf(e, -(CURVE_SCALE / 10)))) * val;
};

void TankChassis::userControl(bool isTank) {
  double leftInput = _controller.Axis3.position();
  double modifiedL = curve(leftInput);
  double leftInputH = _controller.Axis1.position();
  double modifiedLH = curve(leftInputH);
  double rightInput = _controller.Axis2.position();
  double modifiedR = curve(rightInput);
  if (isTank) {
    left.spin(fwd, modifiedL, pct);
    right.spin(fwd, modifiedR, pct);
  } else {
    left.spin(fwd, modifiedL + modifiedLH, pct);
    right.spin(fwd, modifiedL - modifiedR, pct);
  }
}