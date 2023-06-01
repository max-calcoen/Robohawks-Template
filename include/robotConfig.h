/*------------------------------------------------------*/
/*                                                      */
/*    Module:       robotConfig.h                       */
/*    Author:       Max Calcoen (8000A)                 */
/*    Created:      Tue Jan 3 2022                      */
/*    Description:  Robot configuration header file     */
/*                                                      */
/*------------------------------------------------------*/
#pragma once
#include "libs/simpleTemplate/chassis/chassisClass.h"

using namespace vex;

extern brain _brain;
extern controller _controller;
extern competition _competition;

// chassis motors (descriptions are anatomical)
extern motor chassisLF;
extern motor chassisLM;
extern motor chassisLB;
extern motor_group chassisL;

extern motor chassisRF;
extern motor chassisRM;
extern motor chassisRB;
extern motor_group chassisR;

extern TankChassis chassis;

extern triport expander;

extern encoder encoderL;
extern encoder encoderR;
extern encoder encoderB;

extern const double ODOM_WHEEL_DIAMETER;
extern const double ODOM_BACK_DISTANCE;
extern const double ODOM_LEFT_DISTANCE;
extern const double ODOM_RIGHT_DISTANCE;

extern inertial _inertial;
