#include "vex.h" // vex standard library
#include "libs/simpleTemplate/GUI/guiComponents.h" // gui classes
#include "libs/simpleTemplate/auton/autonClass.h" // auton class
#include "robotFunctions.h" // robot functions
#include "libs/simpleTemplate/auton/autons.h" // autons
#include <iostream>
#include <vector>
#include <sstream>
#include <string.h>

const int MAX_SCREEN_HEIGHT = 240;
const int MAX_SCREEN_WIDTH= 480;

//------------------------GUI-Methods---------------------------------

/**
 * Resets pen defaults for drawing on the brain.
 */
void resetBrainPenDefaults() {
  _brain.Screen.setPenColor("#FFFFFF");
  _brain.Screen.setCursor(1, 1);
  _brain.Screen.setFillColor("#000000");
  _brain.Screen.setFont(monoM);
  _brain.Screen.setPenWidth(0);
}
//------------------------Pregame-GUI----------------------------------


std::vector<Auton> redAutons;
std::vector<Auton> blueAutons;

// track the current screen
int currentScreen = 0;
// track the current auton selected
int currentAutonSelected;

// declare onpress functions
void setRed();
void setBlue();
void setRed();
void loadButtons();
void next();
void prevAuton();
void nextAuton();
void calibrate();
void primeComp();

// declare general that helpers need
void updateScreen();
void throwError();

std::vector<Button> screens[] = {
  // select color
  std::vector<Button>{
    Button(MAX_SCREEN_WIDTH / 2 - 150 / 2, 20, 150, 40, "SELECT COLOR", "#FF00FF"),
    Button(MAX_SCREEN_WIDTH / 4 - 100 / 2, 75, 100, 100, "", "#FFFFFF", "#FF0000", setRed),
    Button(3 * MAX_SCREEN_WIDTH / 4 - 100 / 2, 75, 100, 100, "", "#FFFFFF", "#0000FF", setBlue),
    Button(MAX_SCREEN_WIDTH / 2 - 150 / 2, MAX_SCREEN_HEIGHT - 40, 150, 40, "Selected: Red", "#FF0000"),
    Button(MAX_SCREEN_WIDTH - 140, MAX_SCREEN_HEIGHT - 30, 140, 30, "Team Selected", "#000000", "#FFFFFF", [] {
      loadButtons();
      next();
    }),
  },
  // select auton
  std::vector<Button>{
    // title
    Button(MAX_SCREEN_WIDTH / 2 - 200 / 2, 20, 200, 20, "SELECT RED AUTON"),
    // name
    Button(MAX_SCREEN_WIDTH / 2 - 300 / 2, 60, 300, 20, "name"),
    // description line 1
    Button(MAX_SCREEN_WIDTH / 2 - 300 / 2, 80, 300, 20, "description line 1"),
    // description line 2
    Button(MAX_SCREEN_WIDTH / 2 - 300 / 2, 100, 300, 20, "description line 2"),
    // prev auton
    Button(0, MAX_SCREEN_HEIGHT / 2 - 40 / 2, 40, 40, "<", "#000000", "#FFFFFF", prevAuton),
    // next auton
    Button(MAX_SCREEN_WIDTH - 30, MAX_SCREEN_HEIGHT / 2 - 40 / 2, 40, 40, ">", "#000000", "#FFFFFF", nextAuton),
    // next screen
    Button(MAX_SCREEN_WIDTH - 140, MAX_SCREEN_HEIGHT - 30, 140, 30, "Auton Selected", "#000000", "#FFFFFF", [] {
      next();
    }),
  },
  std::vector<Button>{
    Button(MAX_SCREEN_WIDTH / 2 - 200 / 2, MAX_SCREEN_HEIGHT / 2 - 80 / 2, 200, 80, "Position robot now!", "#FFFFFF", "#000000", [] {}),
    Button(MAX_SCREEN_WIDTH - 240, MAX_SCREEN_HEIGHT - 30, 240, 30, "Continue to Calibration", "#FFFFFF", "#000000", [] {
      next();
      calibrate();
    }),
  },
  std::vector<Button>{
    Button(0, 0, MAX_SCREEN_WIDTH, MAX_SCREEN_HEIGHT, "Calibrating...", "#000000", "#FF0000"),
    Button(MAX_SCREEN_WIDTH - 150, MAX_SCREEN_HEIGHT - 40, 150, 40, "Ready!", "#FFFFFF", "00FF00", primeComp),
  },
};

// helper functions

void updateSelectedAutonColor() {
  std::string newLabel = std::string("Selected: ") + std::string((teamRed ? "Red" : "Blue")); 
  // assign label
  screens[0][3].label = newLabel;
}

void setRed() {
  screens[0][3].penColor = "#FF0000";
  teamRed = true;
  _competition.autonomous(redAutons[0].routine);
  updateSelectedAutonColor();
}

void setBlue() {
  screens[0][3].penColor = "#0000FF";
  teamRed = false;
  _competition.autonomous(blueAutons[0].routine);
  updateSelectedAutonColor();
}


void updateAutonButtons() {
  Auton curr = teamRed ? redAutons[currentAutonSelected] : blueAutons[currentAutonSelected];
  _competition.autonomous(curr.routine);
  // name
  screens[1][1].label = "name: " + curr.name;

  // hide desc 2
  screens[1][3].visible = false;
  // we have 360 pixels of space, each character is 10 pixels wide, we have 30 characters first line, 36 characters next
  if (curr.description.length() > 24) {
    // unhide desc 2
    screens[1][3].visible = true;
    std::string firstLine = curr.description.substr(0, 23) + std::string("-");
    std::string secondLine = curr.description.substr(23, 27) + std::string("...");
    screens[1][2].label = "desc: " + firstLine;
    screens[1][3].label = secondLine;
  } else {
    screens[1][2].label = "desc: " + curr.description;;
  }
  
  // remove "next" or "prev" buttons if not applicable
  screens[1][5].visible = true;
  screens[1][6].visible = true;

  if (currentAutonSelected == 0) {
    screens[1][5].visible = false;
  }
  if (currentAutonSelected == (teamRed ? redAutons.size() - 1 : blueAutons.size() - 1)) {
    screens[1][6].visible = false;
  }
}

void loadButtons() {
  screens[1][0].label = teamRed ? "SELECT RED AUTON" : "SELECT BLUE AUTON";
  updateAutonButtons();
}

void next() {
  currentScreen++;
}

void prevAuton() {
  currentAutonSelected--;
  updateAutonButtons();
};

void nextAuton(){
  currentAutonSelected++;
  updateAutonButtons();
};

void calibrate() {
  // visuals
  screens[3][1].visible = false;
  updateScreen();
  // calibrate inertial sensor
  _inertial.calibrate();
  waitUntil(!_inertial.isCalibrating());
  _controller.rumble("..");
  // continue
  screens[3][0].fillColor = "#00FF00";
  screens[3][0].label = "Done!";
  screens[3][1].visible = true;
}

void primeComp() {
  // check that everything is plugged in
  if (
    !(
      chassisLF.installed() && 
      chassisLM.installed() &&
      chassisLB.installed() &&
      chassisRF.installed() &&
      chassisRB.installed() &&
      chassisRM.installed() &&
      _inertial.installed()
    )
  ) {
    throwError();
  }

  resetBrainPenDefaults();

  // user control
  _controller.Axis1.changed([] {
    chassis.userControl(true);
  });
  _controller.Axis2.changed([] {
    chassis.userControl(true);
  });
  _controller.Axis3.changed([] {
    chassis.userControl(true);
  });
  _controller.Axis4.changed([] {
    chassis.userControl(true);
  });

  // button press trackers 
  _controller.ButtonL1.pressed([] {

  });
  _controller.ButtonL2.pressed([] {
    
  });
  _controller.ButtonR1.pressed([] {
    
  });
  _controller.ButtonR2.pressed([] {
    
  });
  _controller.ButtonUp.pressed([] {
    
  });
  _controller.ButtonDown.pressed([] {
    
  });
  _controller.ButtonLeft.pressed([] {
    
  });
  _controller.ButtonRight.pressed([] {
    
  });
  _controller.ButtonX.pressed([] {
    
  });
  _controller.ButtonY.pressed([] {
    
  });
  _controller.ButtonA.pressed([] {
    
  });
  _controller.ButtonB.pressed([] {
    
  });
  comp = true;
}

// general screen functions

void updateScreen() {
  _brain.Screen.clearScreen();
  for (Button button : screens[currentScreen])
    button.draw();
  resetBrainPenDefaults();
}

void GUIInit() {
  for (Auton auton : autons) {
    if (auton.isRed)
      redAutons.push_back(auton);
    else
      blueAutons.push_back(auton);
  }
  updateScreen();
}

/** 
 * Triggers correct button on screen press.
*/
void screenPressed() {

  for (Button butt : screens[currentScreen]) {
    if (
        !(_brain.Screen.xPosition() < butt.posx) && // not left
        !(_brain.Screen.xPosition() > butt.posx + butt.width) && // not right
        !(_brain.Screen.yPosition() < butt.posy) && // not above
        !(_brain.Screen.yPosition() >= butt.posy + butt.height) // not below
        && butt.visible
      ) {
      butt.clicked();
    }
  }
  _brain.Screen.clearScreen();
  updateScreen();
  resetBrainPenDefaults();
}

void throwError() {
  _brain.Screen.clearScreen();
  _brain.Screen.setFillColor("#FF0000");
  _brain.Screen.drawRectangle(0, 0, MAX_SCREEN_WIDTH, MAX_SCREEN_HEIGHT);
  resetBrainPenDefaults();
  _brain.Screen.setCursor(5, 1);
  _brain.Screen.print("ERROR: MOTOR OR INERTIAL SENSOR UNPLUGGED");
  _brain.Screen.newLine();
  _brain.Screen.print("press X on controller or click screen after");
  _brain.Screen.newLine();
  _brain.Screen.print("3 sec to bypass");
  vex::wait(3, sec);
  waitUntil (_controller.ButtonX.pressing() || _brain.Screen.pressing());
}

void skipGUI(Auton a, bool wait=false) {
  if (wait) {
    _inertial.calibrate();
    while (_inertial.isCalibrating()) vex::wait(5, msec);
  }
  _competition.autonomous(a.routine);
  _brain.Screen.clearScreen();
  primeComp();
  comp = true;
}

//----------------------Competition-GUI--------------------------------

void compGUI() {
  _brain.Screen.clearScreen();
  _brain.Screen.setCursor(1, 1);
  _brain.Screen.newLine();
  _brain.Screen.print("Heading (deg): %f", _inertial.heading());
}

//------------------------GUI-Control----------------------------------

void GUI() {
  compGUI();
}