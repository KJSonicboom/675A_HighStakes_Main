#include "main.h"
#include "pros/distance.hpp"
#include "pros/misc.h"
#include "pros/motors.h"
#include <string>

using namespace pros;

//get_digital = gets raw controller button input
//get_didgital_new_press = ensures that a button is being let go and pressed again

//manual lift control
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

//doinker control
void doinking()
{
    bool isDoinking = false;

    while(true){
        if(controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_Y)){
            if(isDoinking){
                doinker.set_value(LOW);
                isDoinking = false;
            }
            else {
                doinker.set_value(HIGH);
                isDoinking = true;
            }
        }
        delay(100);
    }
}

//is being used now
void eat(){

    bool isColorSorting = true; //controls the toggle between color sorting and not color sorting

    while(true){

        //toggles between color sorting and not color sorting (LED matches status)
        if(controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_B)){
            isColorSorting = !isColorSorting;
            if(isColorSorting) intakeSensor.set_led_pwm(100); //turns light on to show enabled
            else if(!isColorSorting) intakeSensor.set_led_pwm(0); //turns light off to show not enabled 
        }

        //basic intake control
        if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_R1)){
            intake.move_velocity(-600); //intake 
            if(isColorSorting) colorSorter();//color sort
        }
        else if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_R2)){
            intake.move_velocity(300); //outake
        }
        else{
            intake.move_velocity(0); //stop
        }

        delay(10);
    }

}

//tilter control
void holdTilter(){

    bool isTilting = false;

    while(true){
        if(controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_A)){
            if(isTilting){
                tilter.set_value(LOW);
                isTilting = false;
            }
            else {
                tilter.set_value(HIGH);
                isTilting = true;
            }
        }
        delay(10);
    }
}

//only for testing purposes
void elevateIntake(){

    bool isIntakeElevated = false;

    while(true){
        if(controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_LEFT)){
            if(isIntakeElevated){
                intakePiston.set_value(LOW);
                isIntakeElevated = false;
            }
            else {
                intakePiston.set_value(HIGH);
                isIntakeElevated = true;
            }
        }
        delay(10);
    }
}

//MACROS-----------------------------------------------------------------------------------------------------------

//toggle that switches between the prime, unprime, and scored state
void liftMacro(){

    arm.set_brake_mode(E_MOTOR_BRAKE_HOLD);

    rotation.reset_position();
    bool isPrimed = false; //prime position refers to when a ring can be intaked into the arm
    bool isScorePosition = false; //isScorePosition is when the arm is in the scored position on the wall stake
    
    while(true){

        double position = rotation.get_position()/100; //current position of the arm

        if(controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_L1)){
            
            isScorePosition = false; //ensures that whenever L2 is pressed it doesn't go into the score position

            if(isPrimed){
                //not primed value (a little higher than origin to save the arm from smacking hardstop)
                moveArm(-15, 1500);
                isPrimed = false; 
            }
            else{
                //primed value
                moveArm(-35, 1500);
                isPrimed = true;
            }
        }
        else if(controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_L2)){

            isPrimed = true; //ensures that whenever L1 is pressed it doesn't go into the primed position

            if(isScorePosition){
                //scored position
                moveArm(-131, 2000);
                isScorePosition = false;
            }
            else{
                //almost scored position
                moveArm(-90, 1000);
                isScorePosition = true;
            }
            
        }

        delay(10);
    }
}

//not being used (intake macro)
void eatRings(){

    bool isIntakeOn = true;

    while(true){

        //cycle between on and off with R1
        if(controller.get_digital_new_press(DIGITAL_R1)){

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
            intake.move_velocity(300); //this is backwards
        }
        else{
            intake.move_velocity(0);
        }
        
        delay(10);
    }
}

