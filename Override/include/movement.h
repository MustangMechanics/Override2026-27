#ifndef MOVEMENT_H
#define MOVEMENT_H

#include "vex.h"

void initializeExpectedHeading();
void bound(double& value, double lo, double hi);
void updateStartPositions();
double getInches();
void stopDriving();
void driveBrake();
void setBrakeMode(vex::brakeType mode);
double convertDegreesToInches(double degrees);
double convertInchesToDegrees(double inches);
void tankDrive(double leftSpeed, double rightSpeed);
void inchDrive(double distance, double speed = 70);
void turn(double Deg, long maxTime = 3000);
void driveForward(double distance, double speed);
void driveTurn(double degrees, double speed);
void liftUp(double speed);
void liftDown(double speed);
void liftStop();

#endif // MOVEMENT_H