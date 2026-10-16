#include "vex.h"
#include "movement.h"
#include "robot-config.h"

void stopDriving() {
    LeftFront.stop();
    LeftMiddle.stop();
    LeftBack.stop();
    RightFront.stop();
    RightMiddle.stop();
    RightBack.stop();

}

void setBrakeMode(vex::brakeType mode) {
    LeftFront.setBrake(mode);
    LeftMiddle.setBrake(mode);
    LeftBack.setBrake(mode);
    RightFront.setBrake(mode);
    RightMiddle.setBrake(mode);
    RightBack.setBrake(mode);
}

double convertDegreesToInches(double degrees) {
    double inches = degrees / 58.76;
    return inches;
}


double convertInchesToDegrees(double inches) {
    double degrees = inches * 58.76;
    return degrees;
}


void tankDrive(double leftSpeed, double rightSpeed) {
   
    leftSpeed = leftSpeed * 0.12;
    rightSpeed = rightSpeed * 0.12;

    LeftFront.spin(vex::forward, leftSpeed, vex::volt);
    LeftMiddle.spin(vex::forward, leftSpeed, vex::volt);
    LeftBack.spin(vex::forward, leftSpeed, vex::volt);

    RightFront.spin(vex::reverse, rightSpeed, vex::volt);
    RightMiddle.spin(vex::reverse, rightSpeed, vex::volt);
    RightBack.spin(vex::reverse, rightSpeed, vex::volt);

}


void driveForward(double inches, double speed) {
    printf("Drive forward\n");
    double currentPosition = (RightMiddle.position(vex::degrees));
    double startingPosition = convertDegreesToInches(currentPosition);
    double travelDegrees = (inches * 58.76);
    double endPosition = currentPosition + travelDegrees;
    double endPositionInches = convertDegreesToInches(endPosition);
    
    
    long startTime = vex::timer::system();
    
    printf("Starting Position: %f degrees, End Position: %f inches, %f inches\n", travelDegrees, endPositionInches, inches);
    // add number of degrees needed to turn to the current position to get the end position
    tankDrive(speed, speed);
    
    while (true) {
        currentPosition = (RightMiddle.position(vex::degrees));
        double error = endPosition - currentPosition;
        if (fabs(error) < 29.30) {
            break;
        }
        printf("Error: %f degrees\n", error);
        vex::task::sleep(10);
    }
    
    stopDriving();
    long endTime = vex::timer::system();
    currentPosition = (RightMiddle.position(vex::degrees));
    printf("Drive Time: %lu ms  Actual distance: %f inches\n", endTime - startTime, currentPosition - startingPosition);

//void moveToHeight(double inches) {}
}



