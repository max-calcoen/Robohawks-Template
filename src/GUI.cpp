#include "vex.h" // vex standard library
#include "odometry.h" // odom variables
#include "classes/guiComponents.h" // gui classes
#include "classes/autonClass.h" // auton class
#include "robotFunctions.h" // robot functions
#include "autons.h" // autons
#include <sstream>

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

// declare variables and functions
int currentScreen = 1;
char autonIndexLabel = '1';

void resetBrainPenDefaults();
void drawPregameButtons();
void nextScreen();
void screenPressed();
void nextScreenCalibrate();
void nextScreenAutons();
void prevScreen();
void updatePageNum();
void readyComp();
void setRedAutonOne();
void setRedAutonTwo();
void setRedAutonThree();
void setBlueAutonOne();
void setBlueAutonTwo();
void setBlueAutonThree();
void setRed();
void setBlue();

Auton redAutons[] = {
  redRoller,
  redNoRoller,
  redSoloWinpoint,
};

Auton blueAutons[] = {
  blueRoller,
  blueNoRoller,
  blueSoloWinpoint,
};


// pregame screens
Button autonSelectionInitScreen[] = {
  Button(MAX_SCREEN_WIDTH / 2 - 150 / 2, 0, 150, 40, "SELECT COLOR", "#FF00FF"), // title
  Button(MAX_SCREEN_WIDTH / 4 - 100 / 2, 75, 100, 100, "", "#FFFFFF", "#FF0000", setRed),
  Button(3 * MAX_SCREEN_WIDTH / 4 - 100 / 2, 75, 100, 100, "", "#FFFFFF", "#0000FF", setBlue),
  Button(MAX_SCREEN_WIDTH / 2 - 150 / 2, MAX_SCREEN_HEIGHT - 40, 150, 40, "Selected: Red", "#FF0000"), // keep track of current selected auton
  Button(MAX_SCREEN_WIDTH - 140, MAX_SCREEN_HEIGHT - 30, 140, 30, "Team Selected", "#000000", "#FFFFFF", nextScreenAutons), // next
};

Button redAutonSelectionScreen[] = {
  Button(MAX_SCREEN_WIDTH / 2 - 150 / 2, 0, 150, 40, "Select Auton", "#FF0000"), // title
  Button(0, MAX_SCREEN_HEIGHT - 40, 175, 40, "Selected: 1"), // keep track of current selected auton
  Button(130, 50, 250, 40, "NAME // DESCRIPTION"), // table title
  Button(40, 90, 360, 40, "Auton 1: " + redAutons[0].name + " // " + redAutons[0].description, "#FFFFFF", "#000000", setRedAutonOne),
  Button(40, 130, 320, 40, "Auton 2: " + redAutons[1].name + " // " + redAutons[1].description, "#FFFFFF", "#000000", setRedAutonTwo),
  Button(40, 170, 400, 40, "Auton 3: " + redAutons[2].name + " // " + redAutons[2].description, "#FFFFFF", "#000000", setRedAutonThree),
  Button(MAX_SCREEN_WIDTH - 150, MAX_SCREEN_HEIGHT - 30, 150, 30, "Position Robot", "#000000", "#FF6A29", nextScreen), // next
};

Button blueAutonSelectionScreen[] = {
  Button(MAX_SCREEN_WIDTH / 2 - 150 / 2, 0, 150, 40, "Select Auton", "#0000FF"), // title
  Button(0, MAX_SCREEN_HEIGHT - 40, 175, 40, "Selected: 1"), // keep track of current selected auton
  Button(130, 50, 250, 40, "NAME // DESCRIPTION"), // table title
  Button(40, 90, 360, 40, "Auton 1: " + blueAutons[0].name + " // " + blueAutons[0].description, "#FFFFFF", "#000000", setBlueAutonOne),
  Button(40, 130, 320, 40, "Auton 2: " + blueAutons[1].name + " // " + blueAutons[1].description, "#FFFFFF", "#000000", setBlueAutonTwo),
  Button(40, 170, 400, 40, "Auton 3: " + blueAutons[2].name + " // " + blueAutons[2].description, "#FFFFFF", "#000000", setBlueAutonThree),
  Button(MAX_SCREEN_WIDTH - 150, MAX_SCREEN_HEIGHT - 30, 150, 30, "Position Robot", "#000000", "#650BDE", nextScreen), // next
};

Button positionScreen[] = {
  Button(MAX_SCREEN_WIDTH / 2 - 200 / 2, MAX_SCREEN_HEIGHT / 2 - 80 / 2, 200, 80, "Position robot now!", "#FFFFFF", "#000000", [] {}),
  Button(MAX_SCREEN_WIDTH - 240, MAX_SCREEN_HEIGHT - 30, 240, 30, "Continue to Calibration", "#FFFFFF", "#000000", nextScreenCalibrate),
};

Button calibratingScreen[] = {
  Button(0, 0, MAX_SCREEN_WIDTH, MAX_SCREEN_HEIGHT, "Calibrating...", "#000000", "#FF0000"),
  Button(MAX_SCREEN_WIDTH - 150, MAX_SCREEN_HEIGHT - 40, 150, 40, "Ready!", "#FFFFFF", "00FF00", readyComp),
};

// button logic
/** 
 * Triggers correct button on screen press.
*/
void screenPressed() {
  // check if current page buttons clicked
  switch (currentScreen) {
    case 1:
      for (Button butt : autonSelectionInitScreen) {
        if (!(_brain.Screen.xPosition() < butt.posx) && !(_brain.Screen.xPosition() > butt.posx + butt.width) && !(_brain.Screen.yPosition() < butt.posy) && !(_brain.Screen.yPosition() >= butt.posy + butt.height && butt.visible)) {
          butt.clicked();
        }
      }
      break;
    case 2:
      for (Button butt : (teamRed ? redAutonSelectionScreen : blueAutonSelectionScreen)) {
        if (!(_brain.Screen.xPosition() < butt.posx) && !(_brain.Screen.xPosition() > butt.posx + butt.width) && !(_brain.Screen.yPosition() < butt.posy) && !(_brain.Screen.yPosition() >= butt.posy + butt.height && butt.visible)) {
          butt.clicked();
        }
      }
      break;
    case 3:
      for (Button butt : positionScreen) {
        if (!(_brain.Screen.xPosition() < butt.posx) && !(_brain.Screen.xPosition() > butt.posx + butt.width) && !(_brain.Screen.yPosition() < butt.posy) && !(_brain.Screen.yPosition() >= butt.posy + butt.height && butt.visible)) {
          butt.clicked();
        }
      }
      break;
    case 4:
      for (Button butt : calibratingScreen) {
        if (!(_brain.Screen.xPosition() < butt.posx) && !(_brain.Screen.xPosition() > butt.posx + butt.width) && !(_brain.Screen.yPosition() < butt.posy) && !(_brain.Screen.yPosition() >= butt.posy + butt.height) && butt.visible) {
          butt.clicked();
        }
      }
      break;
  }
  _brain.Screen.clearScreen();
  drawPregameButtons();
  resetBrainPenDefaults();
}

/** 
* Draw each visible button. Set up brain touch sensing.
*/
void drawPregameButtons() {
  // draw buttons on current page
  switch (currentScreen) {
    case 1:
      for (Button butt : autonSelectionInitScreen)
        butt.draw();
      return;
    case 2:
      for (Button butt : (teamRed ?  redAutonSelectionScreen : blueAutonSelectionScreen))
        butt.draw();
      return;
    case 3:
      for (Button butt : positionScreen)
        butt.draw();
      return;
    case 4:
      for (Button butt : calibratingScreen)
        butt.draw();
      return;
  }
}


/** 
* Go to next screen.
* Triggered on next button press.
*/
void nextScreen() {
  currentScreen++;
}

void nextScreenAutons() {
  if (teamRed) _competition.autonomous(redAutons[0].routine);
  else _competition.autonomous(blueAutons[0].routine);
  currentScreen++;
}

void nextScreenCalibrate() {
  // display
  currentScreen++;
  calibratingScreen[1].visible = false;
  drawPregameButtons();
  // calibrate
  odomInit();

  // continue
  calibratingScreen[0].label = "Done!";
  calibratingScreen[0].fillColor = "#00FF00";
  calibratingScreen[1].visible = true;
}

/** 
* Go to previous screen.
* Triggered on previous button press.
*/
void prevScreen() {
  currentScreen--;
}


/**
* Update the "auton selected" label in the pregame menu.
*/
void updateAutonSelected() {
  // add prefix
  std::string newLabel = std::string("Selected: ") + autonIndexLabel;
  redAutonSelectionScreen[1].label = newLabel;
  // assign label
  if (teamRed) redAutonSelectionScreen[1].label = newLabel;
  else blueAutonSelectionScreen[1].label = newLabel;
}

void setRedAutonOne() {
  autonIndexLabel = '1';
  _competition.autonomous(redAutons[0].routine);
  updateAutonSelected();
}

void setRedAutonTwo() {
  autonIndexLabel = '2';
  _competition.autonomous(redAutons[1].routine);
  updateAutonSelected();
}

void setRedAutonThree() {
  autonIndexLabel = '3';
  _competition.autonomous(redAutons[2].routine);
  updateAutonSelected();
}

void setBlueAutonOne() {
  autonIndexLabel = '1';
  _competition.autonomous(blueAutons[0].routine);
  updateAutonSelected();
}

void setBlueAutonTwo() {
  autonIndexLabel = '2';
  _competition.autonomous(blueAutons[1].routine);
  updateAutonSelected();
}

void setBlueAutonThree() {
  autonIndexLabel = '3';
  _competition.autonomous(blueAutons[2].routine);
  updateAutonSelected();
}

// set comp to true
void readyComp() {
  // check that everything is plugged in
  if (!(
    chassisLF.installed() && 
    chassisLM.installed() &&
    chassisLB.installed() &&
    chassisRF.installed() &&
    chassisRB.installed() &&
    chassisRM.installed() &&
    _inertial.installed()
  ) &&
    // bypass: hold X button on controller
    !_controller.ButtonX.pressing()
  ) {
      _brain.Screen.clearScreen();
      _brain.Screen.setFillColor("#FF0000");
      _brain.Screen.drawRectangle(0, 0, MAX_SCREEN_WIDTH, MAX_SCREEN_HEIGHT);
      resetBrainPenDefaults();
      _brain.Screen.setCursor(5, 1);
      _brain.Screen.print("ERROR: MOTOR OR INERTIAL SENSOR UNPLUGGED");
      _brain.Screen.newLine();
      _brain.Screen.print("restart program & hold X on controller to bypass");
      while (true);
  }


  resetBrainPenDefaults();

  // user control
  _controller.Axis1.changed([] {
    chassis.userControl(true); // tank
  });
  _controller.Axis2.changed([] {
    chassis.userControl(true); // tank
  });
  _controller.Axis3.changed([] {
    chassis.userControl(true); // tank
  });
  _controller.Axis4.changed([] {
    chassis.userControl(true); // tank
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

void updateSelectedAutonColor() {
  std::string newLabel = std::string("Selected: ") + std::string((teamRed ? "Red" : "Blue")); 
  // assign label
  autonSelectionInitScreen[3].label = newLabel;
}

/* 
* Sets selected auton to red.
*/
void setRed() {
  autonSelectionInitScreen[3].penColor = "#FF0000";
  teamRed = true;
  updateSelectedAutonColor();
}

/* 
* Sets selected auton to red.
*/
void setBlue() {
  autonSelectionInitScreen[3].penColor = "#0000FF";
  teamRed = false;
  updateSelectedAutonColor();
}

void skipGUI() {
  nextScreenAutons();
  nextScreen();
  nextScreenCalibrate();
  vex::task::sleep(3000);
  readyComp();
}

//----------------------Competition-GUI--------------------------------

void compGUI() {
  _brain.Screen.clearScreen();
  _brain.Screen.setCursor(1, 1);
  _brain.Screen.print("Global X: %f", globalX);
  _brain.Screen.newLine();
  _brain.Screen.print("Global Y: %f", globalY);
  _brain.Screen.newLine();
  _brain.Screen.print("Heading (deg): %f", _inertial.heading());
}

//------------------------GUI-Control----------------------------------

void GUI() {
  if (comp) compGUI();
}

// idk what this is but it's here -max
double sinceCalibrate;
void timerReset(double toTime){
  toTime = 0;
}

void timerIncriment(double incrimentBy){
  sinceCalibrate += incrimentBy;
}
