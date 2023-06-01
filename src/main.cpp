/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       Max Calcoen (8000A)                                       */
/*    Created:      Tue Jan 3 2022                                            */
/*    Version:      v0.1                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// include necessary imports
#include "vex.h"
// #include "libs/simpleTemplate/GUI/GUI.h"

/*
 *...................User Guide...................
 * {INCLUDES}
 * Skeleton project
 * Chassis class
 * GUI, support for 2 autons per color (will include more buttons in the future)
 * Auton class implemented with odom
 * {NOTES}
 * Odom not implemented (depends on num tracking wheels)
 * This is the first iteration, might not include certain things
 * Create/edit autons in autons.h
 * {TODO}
 * Rename project
 * Configure ports
 * Add robot functions
 * Add autons
*/

// .............dev todo............
// add better button layout (three tabs- red blue skills)
// directions in every file
// robot config notes
// add and normalize comments
// move user guide to README
// test everything- skip gui, gui

int main() {
  // _brain.Screen.pressed([] { if(!comp) screenPressed(); });
  // GUIInit();
  // skipGUI(); // skip gui (commented for ease of access)

  // competition GUI
  vex::thread GUIThread([] {
    waitUntil(comp);
    while (true) {
      // GUI();
      vex::this_thread::sleep_for(15);
    }
  });

  while (true) {
    // main thread will be checking for button presses
    // sleep tick- don't need to run constantly
    vex::task::sleep(20);
  }
  return 0;
}
