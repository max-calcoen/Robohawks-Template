/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       Max Calcoen (8000A)                                       */
/*    Created:      Tue Jan 3 2022                                            */
/*    Version:      v1.0                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// include necessary imports
#include "vex.h"
#include "gui.h"

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
*/

int main() {
  _brain.Screen.pressed([] { if(!comp) screenPressed(); });
  drawPregameButtons();
  // skipGUI(); // skip gui (commented for ease of access)

  // competition GUI
  vex::thread GUIThread([] {
    waitUntil(comp);
    while (true) {
      GUI();
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
