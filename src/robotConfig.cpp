/*------------------------------------------------------*/
/*                                                      */
/*    Module:       robotConfig.cpp                     */
/*    Author:       Max Calcoen (8000A)                 */
/*    Created:      Tue Jan 3 2022                      */
/*    Function:     Configure robot devices             */
/*                                                      */
/*------------------------------------------------------*/
#include "vex.h"
#include "libs/simpleTemplate/chassis/chassisClass.h"

using namespace vex;

brain _brain;
controller _controller;
competition _competition;

motor intakeAndIndexer(PORT1);

// chassis motors (descriptions are anatomical)
motor chassisLF = motor(PORT1, ratio18_1, false);
motor chassisLM = motor(PORT10, ratio18_1, false);
motor chassisLB = motor(PORT10, ratio18_1, false);
motor_group chassisL(chassisLF, chassisLM, chassisLB);

motor chassisRF = motor(PORT1, ratio18_1, false);
motor chassisRM = motor(PORT10, ratio18_1, false);
motor chassisRB = motor(PORT10, ratio18_1, false);
motor_group chassisR(chassisRF, chassisRM, chassisRB);

TankChassis chassis(chassisL, chassisR,
  // c++ doesn't support named parameters :(
  3.25, // wheel diameter
  2.5,  // p
  0.01, // i
  0.5,  // d
  2.0,  // turn p
  0.01, // turn i
  1.0   // turn d
);

inertial _inertial(PORT5);

triport expander(PORT1);

encoder encoderL(expander.A);
encoder encoderR(expander.B);
encoder encoderB(expander.C);

const double ODOM_WHEEL_DIAMETER = 3.25;
const double ODOM_BACK_DISTANCE = 2.25;
const double ODOM_LEFT_DISTANCE = 4.25;
const double ODOM_RIGHT_DISTANCE = 3.25;
