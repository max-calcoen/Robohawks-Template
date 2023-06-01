#pragma once
#include "v5.h"

using namespace vex;

class Chassis {
  protected:
    motor_group left;
    motor_group right;
    drivetrain dt;
    double kP;
    double kI;
    double kD;
    double turnKP;
    double turnKI;
    double turnKD;
  public:
    const double WHEEL_DIAMETER;
    Chassis(motor_group l, motor_group r, double WHEEL_DIAMETER, double kP,  double kI, double kD, double turnKP, double turnKI, double turnKD);
    // user control functions
    virtual void userControl(bool isTank) = 0;

    // autonomous functions
    // pid
    virtual void drive(directionType dir, double dist, double speed) = 0;
    virtual void drive(directionType dir, double dist, double speed, double kP, double kI, double kD) = 0;
    virtual void turnTo(double angle, double vel) = 0;
    // set Ks for finer tuning
    void setK(double kP, double kI, double kD);
    // set brake type
    void setStopping(brakeType bT) {
      dt.setStopping(bT);
    }
};

class TankChassis : Chassis {
  using Chassis::Chassis; // using parent constructor
  private:
    // Bounds the given value to the interval [min, max]
    inline double _limit(double val, double min, double max);
    inline double curve(double val);
  public:
    void turnTo(double, double) override;
    void drive(directionType dir, double dist, double speed) override;
    // set P, I and D for finer tuning
    void drive(directionType dir, double dist, double speed, double kP, double kI, double kD) override;
    void userControl(bool isTank) override;
};