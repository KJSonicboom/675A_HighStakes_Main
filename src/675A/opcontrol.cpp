#include "main.h"
#include "pros/distance.hpp"
#include "pros/misc.h"
#include "pros/motors.h"
#include <string>

using namespace pros;

// std::string rotate = std::to_string(position);
// controller.set_text(0, 0, rotate);

void lift(){

    arm.set_brake_mode(MotorBrake::hold);

    while(true){

        if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_UP)){
            arm.move_velocity(-120);
        }
        else if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_DOWN)){//y
            arm.move_velocity(120);
        }
        else{
            arm.move_velocity(0);
        }

        delay(10);
    }
}

void doinking()
{
    bool isDoinking = false;

    while(true){
        if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_Y)){
            if(isDoinking){
                doinker.set_value(LOW);
                isDoinking = false;
                delay(500);
            }
            else {
                doinker.set_value(HIGH);
                isDoinking = true;
                delay(500);
            }
        }
        delay(100);
    }
}

//not being used
void eat(){

    while(true){

        if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_X)){
            intake.move_velocity(-600);
        }
        else if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_B)){
            intake.move_velocity(600);
        }
        else{
            intake.move_velocity(0);
        }

        delay(10);
    }

}

void holdTilter(){

    bool isTilting = false;

    while(true){
        if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_A)){
            if(isTilting){
                tilter.set_value(LOW);
                isTilting = false;
                delay(500);
            }
            else {
                tilter.set_value(HIGH);
                isTilting = true;
                delay(500);
            }
        }
        delay(100);
    }
}

//pid (will make into seperate file if i can get it to work)--------------------------------------------
const double FIRST_RING_LIFT_VALUE = -0.095 * 360 * 100; 

double kP = 0.05;  
double kI = 0.0;  
double kD = 0.5; 

double error = 0, last_error = 0, integral = 0, derivative = 0;
double targetLiftValue = FIRST_RING_LIFT_VALUE;

void stopLift() {
    arm.move_velocity(0);
    integral = 0;
    last_error = 0;
}

void liftAutoControl(double targetLiftValue = FIRST_RING_LIFT_VALUE) {
    double resetValue;

      double currentLiftValue = rotation.get_position()/100;  
      if (targetLiftValue == -1) {
          double resetValue = -0.02 * 360 * 100; 
          error = resetValue - currentLiftValue;
      } else {
          error = targetLiftValue - currentLiftValue;
      }
      
      if (abs(error) < 5) {  
          stopLift();
          return;
      }

      integral += error;
      derivative = error - last_error;
      double motorSpeed = -1 * ((error * kP) + (integral * kI) + (derivative * kD));  
      
      motorSpeed = std::clamp(motorSpeed, -200.0, 200.0); //clamp forces the input to be in range of -200 to 200
      arm.move_velocity(motorSpeed);

      last_error = error;
}

//only used in auton
void elevateIntake(){

    bool isIntakeElevated = false;

    while(true){
        if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_LEFT)){
            if(isIntakeElevated){
                intakePiston.set_value(LOW);
                isIntakeElevated = false;
                delay(500);
            }
            else {
                intakePiston.set_value(HIGH);
                isIntakeElevated = true;
                delay(500);
            }
        }
        delay(100);
    }
}

//MACROS-----------------------------------------------------------------------------------------------------------

void liftMacro(){

    rotation.reset_position();
    bool isPrimed = false;
    
    while(true){

        double position = rotation.get_position()/100;

        if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_L1)){

            delay(100);
            
            if(isPrimed == false){
                //primed value
                // while(position > -27){ 
                //     arm.move_velocity(-70);
                //     position = rotation.get_position()/100;
                // }
                
                isPrimed = true; 
            }
            else{
                while(position < 0){ 
                    arm.move_velocity(70);
                    position = rotation.get_position()/100;
                }
                isPrimed = false;
            }
        }
        else if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_L2)){
            while(position > -131){
                arm.move_velocity(-120);
                position = rotation.get_position()/100;

            }
            isPrimed = false;
        }

        delay(10);
    }
}

void eatRings(){

    bool isIntakeOn = true;

    while(true){

        if(isRingValid() == 1) controller.set_text(0, 0, "valid");
        else if(isRingValid() == 2) controller.set_text(0, 0, "error");
        else if (isRingValid() == 0) controller.set_text(0, 0, "nothing");
        
        std::string col = std::to_string(intakeSensor.get_hue());
        controller.set_text(0, 5, col);

        //cycle between on and off with R1
        if(controller.get_digital(DIGITAL_R1)){

            delay(200); //acount for human error

            isIntakeOn = !isIntakeOn;

            while(!controller.get_digital(DIGITAL_R2)){
            
                if(isIntakeOn){
                    intake.move_velocity(0);// this is off
                }
                else {
                    intake.move_velocity(-600); //this is forwards
                    colorSorter();
                }

                if(controller.get_digital(DIGITAL_R1)) break;
            }

        }
        else if (controller.get_digital(DIGITAL_R2)){
            intake.move_velocity(200); //this is backwards
        }
        else{
            intake.move_velocity(0);
        }
        
        delay(10);
    }
}

//HELPERS----------------------------------------------------------------------------------------------------------

void colorSorter(){
    if(isRingValid() == 2){
        delay(120);
        intake.move_velocity(0);
        delay(150);
        intake.move_velocity(600);
    } 
}

void runIntake(int time){
    intake.move_velocity(600);
    delay(time);
    intake.move_velocity(0);
}

int isRingValid(){

    isRedTeam = true;

    intakeSensor.set_led_pwm(100);

    if(isRedTeam){
        if(intakeSensor.get_hue() < 22) return 1; 
        else if(intakeSensor.get_hue() > 100) return 2;
        else return 0;
    }
    else{
        if(intakeSensor.get_hue() > 100) return 1;
        else if(intakeSensor.get_hue() < 22) return 2;
        else return 0;
    }

}

//AUTON HELPERS----------------------------------------------------------------------------------------------------------

//moves relative to the robot
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

//finish later
void raiseIntake(bool isUp){
    // if(isUp){

    // }
}