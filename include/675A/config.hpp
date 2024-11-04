#include "api.h"
#include "lemlib/api.hpp" // IWYU pragma: keep
using namespace pros;

inline Controller controller (CONTROLLER_MASTER);
inline Imu imu (2); 

inline Motor left_front_motor(6, pros::v5::MotorGears::blue);
inline Motor left_middle_motor(18, pros::v5::MotorGears::blue);
inline Motor left_back_motor(20, pros::v5::MotorGears::blue);

inline MotorGroup leftMotors({-20, -18, -6}, pros::MotorGearset::blue);

inline Motor right_front_motor(-9, pros::v5::MotorGears::blue);
inline Motor right_middle_motor(-8, pros::v5::MotorGears::blue); 
inline Motor right_back_motor(4, pros::v5::MotorGears::blue);

inline MotorGroup rightMotors({9, 8, 4}, pros::MotorGearset::blue);

inline Motor intake(19, pros::v5::MotorGears::blue);
inline Motor arm(16, pros::v5::MotorGears::green); 

inline adi::DigitalOut tilter('H', LOW);
inline adi::DigitalOut doinker('G', LOW);
inline adi::DigitalOut intakePiston('F', HIGH);

inline Rotation rotation(12); 

inline Distance mogoRange(3);
inline Optical intakeSensor(14);

//Lemlib stuff

inline lemlib::Drivetrain drivetrain(&leftMotors, // left motor group
                              &rightMotors, // right motor group
                              11.5, // 11.5 inch track width
                              lemlib::Omniwheel::NEW_325, // using new 3.25" omnis
                              450, // drivetrain rpm is 450
                              2 // horizontal drift is 2 (idk what this means)
);

// odometry settings
inline lemlib::OdomSensors sensors(nullptr, // vertical tracking wheel 1, set to null
                            nullptr, // vertical tracking wheel 2, set to nullptr as we are using IMEs
                            nullptr, // horizontal tracking wheel 1
                            nullptr, // horizontal tracking wheel 2, set to nullptr as we don't have a second one
                            &imu // inertial sensor
);

// lateral PID controller
inline lemlib::ControllerSettings lateral_controller(7, // proportional gain (kP)
                                              0, // integral gain (kI)
                                              25, // derivative gain (kD)
                                              0, // anti windup
                                              1, // small error range, in inches
                                              100, // small error range timeout, in milliseconds
                                              2, // large error range, in inches
                                              500, // large error range timeout, in milliseconds
                                              0  // maximum acceleration (slew): use if acceleration is too high
);                                       

// angular PID controller
inline lemlib::ControllerSettings angular_controller(5, // proportional gain (kP) 
                                              0, // integral gain (kI) 
                                              48, // dervative gain (kD) 
                                              0, // anti windup
                                              1, // small error range, in inches
                                              100, // small error range timeout, in milliseconds
                                              3, // large error range, in inches
                                              500, // large error range timeout, in milliseconds
                                              0 // maximum acceleration (slew)
);

// input curve for throttle input during driver control
inline lemlib::ExpoDriveCurve throttleCurve(3, // joystick deadband out of 127
                                     10, // minimum output where drivetrain will move out of 127
                                     1.024 // expo curve gain
);

// input curve for steer input during driver control
inline lemlib::ExpoDriveCurve steerCurve(3, // joystick deadband out of 127
                                  10, // minimum output where drivetrain will move out of 127
                                  1.019 // expo curve gain
);

// create the chassis
inline lemlib::Chassis chassis(drivetrain, // drivetrain settings
                        lateral_controller, // lateral PID settings
                        angular_controller, // angular PID settings
                        sensors, // odometry sensors
                        &throttleCurve,
                        &steerCurve
);

