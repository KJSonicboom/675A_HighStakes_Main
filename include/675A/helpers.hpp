#include "api.h"

//helpers
void colorSorter();
int getIntakeSensorDistance();
int isRingValid();
void moveArm(int targetDegree, int timeout);

//auton helpers
void moveRelative(float distance, float maxSpeed, int timeout);
void raiseIntake(bool raise);
extern void runIntake(int time, bool isColorSorting = true);
