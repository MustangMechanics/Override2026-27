#include "vex.h"
#include "robot-config.h"

const int HOOP = 0;
const int TILT = 1;
const int CATCHER = 2;

vex::digital_out* actuators[3];

bool isActOpen[] = {false, false, false};

long nextActTime[] = {0, 0, 0};

void initPneumatics() {
    actuators[HOOP] = new vex::digital_out(Brain.ThreeWirePort.A);
    actuators[TILT] = new vex::digital_out(Brain.ThreeWirePort.B);
    actuators[CATCHER] = new vex::digital_out(Brain.ThreeWirePort.C);
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

bool isHoopDown() { return isActOpen[HOOP]; }
void hoopDown() { openActuator(HOOP); }
void hoopUp() { closeActuator(HOOP); }
bool toggleHoop() { return toggleActuator(HOOP); }

bool isTiltOut() { return isActOpen[TILT]; }
void tiltOut() { openActuator(TILT); }
void tiltIn() { closeActuator(TILT); }
bool toggleTilt() { return toggleActuator(TILT); }

bool isCatcherOut() { return isActOpen[CATCHER]; }
void catcherOut() { openActuator(CATCHER); }
void catcherIn() { closeActuator(CATCHER); }
bool toggleCatcher() { return toggleActuator(CATCHER); }