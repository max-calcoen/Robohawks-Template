#pragma once
typedef void (*func)();
class Auton {
public:
  func routine;
  std::string name;
  std::string description;
  double startingX;
  double startingY;
  double startingTheta;
  bool isRed;

  /**
   * Creates an instance of the Auton class.
   * @param {std::string}  name            name of auton
   * @param {std::string}  description     short description of auton routine
   * @param {double}       startingX       starting x position of robot
   * @param {double}       startingY       starting y position of robot
   * @param {double}       startingTheta   starting angle of robot in degrees; 0 degrees from middle of field faces roller on the left, red goal on the left. see {TODO}
   * @param {bool}         isRed           true if robot starts on red side
   * @param {func}         routine         autonomous routine
   */
  Auton(std::string name, std::string description, double startingX, double startingY, double startingTheta, bool isRed, func routine);
  /*
   * Initialize the odom with the correct starting position.
   */
  void init();
};