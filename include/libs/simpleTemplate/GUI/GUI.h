#pragma once
#include "libs/simpleTemplate/auton/autonClass.h"

// define the func type to pass to button constructor
typedef void (*func)();

//--------------------------------------------variables-------------------------------------------------------------------------------

//-------------------------------------------GUI methods-------------------------------------------------------------------------------
void screenPressed();
void skipGUI(Auton a, bool wait=false);
void GUI();
void GUIInit();