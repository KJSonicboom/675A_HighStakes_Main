#include "main.h"
#include "pros/adi.h"
#include "pros/rotation.hpp"
#include "lemlib/api.hpp"

using namespace pros;

Controller controller (CONTROLLER_MASTER);
Imu imu (2); 

Motor left_front_motor(6, pros::v5::MotorGears::blue);
Motor left_middle_motor(18, pros::v5::MotorGears::blue);
Motor left_back_motor(20, pros::v5::MotorGears::blue);

MotorGroup leftMotors({20, -18, -6}, pros::MotorGearset::blue);

Motor right_front_motor(-9, pros::v5::MotorGears::blue);
Motor right_middle_motor(-8, pros::v5::MotorGears::blue); 
Motor right_back_motor(4, pros::v5::MotorGears::blue);

MotorGroup rightMotors({9, 8, 4}, pros::MotorGearset::blue);

Motor intake(19, pros::v5::MotorGears::blue);
Motor arm(16, pros::v5::MotorGears::green); 

adi::DigitalOut tilter('H', LOW);
adi::DigitalOut doinker('G', LOW);
adi::DigitalOut intakePiston('F', HIGH);

Rotation rotation(12); 

Distance mogoRange(3);
Optical intakeSensor(14);

//Lemlib stuff

lemlib::Drivetrain drivetrain(&leftMotors, // left motor group
                              &rightMotors, // right motor group
                              11.5, // 10 inch track width
                              lemlib::Omniwheel::NEW_325, // using new 4" omnis
                              450, // drivetrain rpm is 450
                              2 // horizontal drift is 2 (for now)
);

// odometry settings
lemlib::OdomSensors sensors(nullptr, // vertical tracking wheel 1, set to null
                            nullptr, // vertical tracking wheel 2, set to nullptr as we are using IMEs
                            nullptr, // horizontal tracking wheel 1
                            nullptr, // horizontal tracking wheel 2, set to nullptr as we don't have a second one
                            &imu // inertial sensor
);

// lateral PID controller
lemlib::ControllerSettings lateral_controller(7, // proportional gain (kP)
                                              0, // integral gain (kI)
                                              25, // derivative gain (kD)
                                              0, // anti windup
                                              1, // small error range, in inches
                                              100, // small error range timeout, in milliseconds
                                              2, // large error range, in inches
                                              500, // large error range timeout, in milliseconds
                                              0  // maximum acceleration (slew)
);                                       

// angular PID controller
lemlib::ControllerSettings angular_controller(5, // proportional gain (kP) 
                                              0, // integral gain (kI) 
                                              48, // dervative gain (kD) 
                                              0, // anti windup
                                              1, // small error range, in inches
                                              100, // small error range timeout, in milliseconds
                                              3, // large error range, in inches
                                              500, // large error range timeout, in milliseconds
                                              0 // maximum acceleration (slew)
);

// create the chassis
lemlib::Chassis chassis(drivetrain, // drivetrain settings
                        lateral_controller, // lateral PID settings
                        angular_controller, // angular PID settings
                        sensors // odometry sensors
);