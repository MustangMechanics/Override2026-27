#include "test.h"
#include "movement.h"
#include "robot-config.h"

void testDrive (double inches) {
    double startingPosition = RightMiddle.position(vex::degrees);
    long startTime = vex::timer::system();

    driveForward(inches, 25);

    long endTime = vex::timer::system();
    vex::task::sleep(1000);
    double endingPosition = RightMiddle.position(vex::degrees);

    printf("%f inches, %lu milliseconds, %f inches traveled\n", inches, (endTime - startTime), (endingPosition - startingPosition) / 58.76);

}