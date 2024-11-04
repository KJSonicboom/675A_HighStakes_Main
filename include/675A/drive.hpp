#include "api.h"

inline void arcade_flipped(){
    
    //never do manual drivetrain code again; just use lemlib
    chassis.setBrakeMode(E_MOTOR_BRAKE_BRAKE);

    while(true){

        //arcade control
        int leftY = controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
        int rightX = controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X);

        chassis.arcade(leftY, rightX);

        delay(10);
    }

}