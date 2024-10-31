#include "api.h"

//op control
void lift();
void doinking();
void eatRings();
void eat();
void holdTilter();
void elevateIntake();
void liftMacro();
bool isMogoClose();
//void mogoInRange(); <--- rumble doesn't work

//helpers
void colorSorter();
void runIntake(int time);
int getIntakeSensorDistance();
int isRingValid();

//auton helpers
void moveRelative(float distance, float maxSpeed, int timeout);
void raiseIntake(bool isUp);