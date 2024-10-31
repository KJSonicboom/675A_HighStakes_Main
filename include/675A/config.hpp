#include "api.h"
#include "lemlib/api.hpp" // IWYU pragma: keep
using namespace pros;

extern Controller controller;
extern Imu imu;

extern Motor left_front_motor;
extern Motor left_middle_motor;
extern Motor left_back_motor;

extern Motor right_front_motor;
extern Motor right_middle_motor;
extern Motor right_back_motor;

extern MotorGroup leftMotors;
extern MotorGroup rightMotors;

extern Motor arm;

extern Motor intake;
extern IMU intertial_sensor;

extern adi::DigitalOut tilter;
extern adi::DigitalOut doinker;
extern adi::DigitalOut intakePiston;


extern Rotation rotation;
extern Distance mogoRange;
extern Optical intakeSensor;

extern lemlib::Chassis chassis;