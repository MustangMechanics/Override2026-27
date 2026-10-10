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

    LeftFront.spin(vex::reverse, leftSpeed, vex::volt);
    LeftMiddle.spin(vex::reverse, leftSpeed, vex::volt);
    LeftBack.spin(vex::reverse, leftSpeed, vex::volt);

    RightFront.spin(vex::forward, rightSpeed, vex::volt);
    RightMiddle.spin(vex::forward, rightSpeed, vex::volt);
    RightBack.spin(vex::forward, rightSpeed, vex::volt);

}


void driveForward(double inches, double speed) {
    
    double currentPosition = (RightMiddle.position(vex::degrees));
    double startingPosition = convertDegreesToInches(currentPosition);
    double travelDegrees = (inches * 58.76);
    double endPosition = currentPosition + travelDegrees;
    double endPositionInches = convertDegreesToInches(endPosition);
    long startTime = vex::timer::system();
    

    printf("Starting Position: %f inches, End Position: %f inches, %f inches\n", startingPosition, endPositionInches, inches);
    // add number of degrees needed to turn to the current position to get the end position
    tankDrive(speed, speed);

    while (true) {
        currentPosition = (RightMiddle.position(vex::degrees));
        double error = endPosition - currentPosition;
        if (fabs(error) < 29.30) {
            break;
        }
    }

    stopDriving();
    long endTime = vex::timer::system();
    printf("Drive Time: %lu ms\n", endTime - startTime);
}



