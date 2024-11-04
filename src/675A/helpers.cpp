#include "main.h"
#include "pros/distance.hpp"
#include "pros/misc.h"
#include "pros/motors.h"
#include "lemlib/timer.hpp"
#include <string>

using namespace pros;

/// @brief sorts rings based on a timing
void colorSorter(){
    if(isRingValid() == 2){
        delay(170);
        intake.move_velocity(0);
        delay(150);
        intake.move_velocity(600);
    } 
}

///@brief verifies ring based on color set during auton
int isRingValid(){

    intakeSensor.set_led_pwm(100); //turns the LED light on to show sorting is enabled

    if(isRedTeam){
        if(intakeSensor.get_hue() < 22 && intakeSensor.get_proximity() > 210) return 1; 
        else if(intakeSensor.get_hue() > 100 && intakeSensor.get_proximity() > 210) return 2;
        else return 0;
    }
    else{
        if(intakeSensor.get_hue() > 100 && intakeSensor.get_proximity() > 210) return 1;
        else if(intakeSensor.get_hue() < 22 && intakeSensor.get_proximity() > 210) return 2;
        else return 0;
    }

}

//Arm PID

//Variables
lemlib::PID armPID(4, 0, 40, 0, false); //needs to be tuned a little more to prevent smacking
int currentPosition;
int error;

/// @brief Moves the arm using a PID controller
/// @param targetDegree Target degree of the arm
/// @param timeout Timeout so the PID doesn't run forever
void moveArm(int targetDegree, int timeout){
    error = 10; //this can be any number greater than the accuracy
    lemlib::Timer armTimer(timeout);
    while(abs(error) > 5 && !armTimer.isDone()){
        currentPosition = rotation.get_position()/100;
        error = targetDegree - currentPosition; 
        arm.move(armPID.update(error));
    }
    armPID.reset();
}

//AUTON HELPERS----------------------------------------------------------------------------------------------------------

/// @brief Moves relative to the robot
/// @param distance the distance of the motion
/// @param maxSpeed the max speed during the motion
/// @param timeout exits the motion after the timeout duration
void moveRelative(float distance, float maxSpeed, int timeout) {
    double headingRadians = chassis.getPose(true).theta;
    double startingX = chassis.getPose().x;
    double startingY = chassis.getPose().y;
    double deltaX = distance * sin(headingRadians);
    double deltaY = distance * cos(headingRadians);
    double newX = startingX + deltaX;
    double newY = startingY + deltaY;
    if (distance > 0) {
        chassis.moveToPoint(newX, newY, timeout, {.forwards=true, .maxSpeed=maxSpeed});
    }
    else if (distance < 0) {
        chassis.moveToPoint(newX, newY, timeout, {.forwards=false, .maxSpeed=maxSpeed});
    }
}

/// @brief If you want to raise the intake (mainly for auton purposes)
/// @param raise If you want to raise the intake
void raiseIntake(bool raise){
    if(raise){
        intakePiston.set_value(LOW); //raises intake
    }
    else{
        intakePiston.set_value(HIGH); //lowers intake
    }
}

/// @brief runs intake for a certain time period
/// @param time The amount of time the intake runs for
/// @param isColorSorting If you want the intake to color sort (true by default)
void runIntake(int time, bool isColorSorting){
    intake.move_velocity(600);
    if(isColorSorting) colorSorter();
    delay(time);
    intake.move_velocity(0);
}