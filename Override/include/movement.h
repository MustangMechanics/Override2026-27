#ifndef MOVEMENT_H
#define MOVEMENT_H

#include "vex.h"

void stopDriving();
void setBrakeMode(vex::brakeType mode);
void tankDrive(double leftSpeed, double rightSpeed);
void driveForward(double distance, double speed);


#endif // MOVEMENT_H