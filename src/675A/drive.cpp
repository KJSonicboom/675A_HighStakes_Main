#include "main.h"
#include "pros/abstract_motor.hpp"

//variables
double speedNerf = 1;

double leftSens = 1;
double rightSens = 0.75;

//Left curve function
double left_curve_function(double x) {return (powf(2.718, -.3) + powf(2.718, (fabs(x) - 127) / 10) * (1 - powf(2.718, -.3))) * x * leftSens;}

//Right curve funciton
double right_curve_function(double x) {return (powf(2.718, -.3) + powf(2.718, (fabs(x) - 127) / 10) * (1 - powf(2.718, -.3))) * x * rightSens;}

//Check threshold function
void checkThreshold(int x_dir, int y_dir){
    //Threshold of controller
    int joystickThreshold = 5;

    if(abs(x_dir) > joystickThreshold || abs(y_dir) > joystickThreshold){
        drive(x_dir, y_dir);
    }

    else{
        leftMotors.move_voltage(0);
        rightMotors.move_voltage(0);
    }
}

//Drive Function
void drive(int x_dir, int y_dir){
    left_front_motor.move_voltage(-(y_dir + x_dir) * (12000 / 127) * speedNerf);
    left_middle_motor.move_voltage(-(y_dir + x_dir) * (12000 / 127) * speedNerf);
    left_back_motor.move_voltage(-(y_dir + x_dir) * (12000 / 127) * speedNerf);

    right_front_motor.move_voltage(-(y_dir - x_dir) * (12000 / 127) * speedNerf);
    right_middle_motor.move_voltage(-(y_dir - x_dir) * (12000 / 127) * speedNerf);
    right_back_motor.move_voltage((y_dir - x_dir) * (12000 / 127) * speedNerf);
}

//Arcade function
void arcade_flipped(){

    left_back_motor.set_brake_mode(E_MOTOR_BRAKE_BRAKE);
    left_middle_motor.set_brake_mode(E_MOTOR_BRAKE_BRAKE);
    left_back_motor.set_brake_mode(E_MOTOR_BRAKE_BRAKE);
    
    right_back_motor.set_brake_mode(E_MOTOR_BRAKE_BRAKE);
    right_middle_motor.set_brake_mode(E_MOTOR_BRAKE_BRAKE);
    right_front_motor.set_brake_mode(E_MOTOR_BRAKE_BRAKE);

    while(true){

        int x_dir, y_dir;

        y_dir = left_curve_function(controller.get_analog(E_CONTROLLER_ANALOG_LEFT_Y));
        x_dir = right_curve_function(controller.get_analog(E_CONTROLLER_ANALOG_RIGHT_X));

        checkThreshold(x_dir, y_dir);

        delay(10);
    }
}