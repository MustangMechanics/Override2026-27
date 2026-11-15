#include "vex.h"
#include "robot-config.h"

const int TILT = 0;
const int CLAW = 1;
const int CATCHER = 2;
const int TOGGLE = 3;

vex::digital_out* actuators[4];

bool isActOpen[] = {false, false, false, false};

long nextActTime[] = {0, 0, 0, 0};

void initPneumatics() {
    actuators[TILT] = new vex::digital_out(Brain.ThreeWirePort.B);
    actuators[CLAW] = new vex::digital_out(Brain.ThreeWirePort.E);
    actuators[CATCHER] = new vex::digital_out(Brain.ThreeWirePort.C);
    actuators[TOGGLE] = new vex::digital_out(Brain.ThreeWirePort.D);
}

void openActuator(int index) {
    actuators[index]->set(true);
    isActOpen[index] = true;
}

void closeActuator(int index) {
    actuators[index]->set(false);
    isActOpen[index] = false;
}

bool toggleActuator(int index) {
    long time = vex::timer::system();
    if (time > nextActTime[index]) {
        isActOpen[index] = !isActOpen[index];
        actuators[index]->set(isActOpen[index]);
        nextActTime[index] = time + 500;
        return true;
    }
    return false;
}


bool isTiltOut() { return isActOpen[TILT]; }   
void tiltOut() { openActuator(TILT); }
void tiltIn() { closeActuator(TILT); }
bool toggleTilt() { return toggleActuator(TILT); }

bool isClawClosed() { return isActOpen[CLAW]; }
void openClaw() { closeActuator(CLAW); }
void closeClaw() { openActuator(CLAW); }
bool toggleClaw() { return toggleActuator(CLAW); }

bool isCatcherOut() { return isActOpen[CATCHER]; }
void catcherOut() { openActuator(CATCHER); }
void catcherIn() { closeActuator(CATCHER); }
bool toggleCatcher() { return toggleActuator(CATCHER); }

bool isToggleOut() { return isActOpen[TOGGLE]; }
void toggleOut() { openActuator(TOGGLE); }
void toggleIn() { closeActuator(TOGGLE); }
bool toggleToggle() { return toggleActuator(TOGGLE); }    