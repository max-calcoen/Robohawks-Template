#include "libs/simpleTemplate/auton/autonClass.h"
#include <vector>

/**
 * Creates an instance of the Auton class.
 * @param {std::string}  name            name of auton
 * @param {std::string}  description     short description of auton routine
 * @param {bool}         isRed           true if robot starts on red side
 * @param {func}         routine         autonomous routine
 */


Auton autonsArr[] = {
  Auton("name", "description", true, [] {}),
  Auton("name", "description", true, [] {}),
  Auton("name", "description", true, [] {}),
  Auton("name", "description", true, [] {}),
  Auton("name", "description", true, [] {}),
};



std::vector<Auton> autons(autonsArr, autonsArr + sizeof(autonsArr) / sizeof(Auton));