/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       vex.h                                                     */
/*    Author:       Vex Robotics                                              */
/*    Created:      1 Feb 2019                                                */
/*    Function:     Default header for V5 projects                            */
/*                                                                            */
/*----------------------------------------------------------------------------*/
#pragma once
#include "v5.h"
#include "v5_vcs.h"
#include "robotConfig.h"
#include "matchVars.h"
#include "robotFunctions.h"

#define waitUntil(condition)                                                   \
  do {                                                                         \
    wait(5, msec);                                                             \
  } while (!(condition))

#define repeat(iterations)                                                     \
  for (int iterator = 0; iterator < iterations; iterator++)