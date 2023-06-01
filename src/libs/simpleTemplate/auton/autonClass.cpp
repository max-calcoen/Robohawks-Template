/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       autonClass.cpp                                            */
/*    Author:       Max Calcoen (8000A)                                       */
/*    Created:      Tue Jan 3 2022                                            */
/*    Description:  Header file for auton class                               */
/*                                                                            */
/*----------------------------------------------------------------------------*/
#include "vex.h"
#include "libs/simpleTemplate/auton/autonClass.h"
#include <iostream>

Auton::Auton(std::string name, std::string description, bool isRed, func routine) {
  this->name = name;
  this->description = description;
  this->isRed = isRed;
  this->routine = routine;
}

void Auton::init() {
  teamRed = this->isRed;
}