#pragma once
#include <iostream>
#include "matchVars.h"
typedef void (*func)();

class Auton {
  public:
  func routine;
  std::string name;
  std::string description;
  bool isRed;

  /**
   * Creates an instance of the Auton class.
   * @param {std::string}  name            name of auton
   * @param {std::string}  description     short description of auton routine
   * @param {bool}         isRed           true if robot starts on red side
   * @param {func}         routine         autonomous routine
   */
  Auton(std::string name, std::string description, bool isRed, func routine);
  /*
   * Initialize the odom with the correct starting position.
   */
  void init();
};