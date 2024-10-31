#include "api.h"

//functions defined here
void reset_drive_functions();
double left_curve_function();
double right_curve_function();
void checkThreshold(int x_dir, int y_dir);
void drive(int x_dir, int y_dir);
void arcade_flipped();