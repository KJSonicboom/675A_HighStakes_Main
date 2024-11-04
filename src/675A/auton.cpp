#include "main.h"
#include "pros/adi.h"
#include "lemlib/api.hpp"
#include <future>         

using namespace pros;

//path jerry testing
ASSET(mogoRushV4_txt);

void pathJerryTest(){
    chassis.setPose(-59.163, -62.11, 90); //initial position has to be the same as the first two numberes in the txt file
    chassis.follow(mogoRushV4_txt, 20, 15000);
    chassis.waitUntilDone();
    runIntake(-2000);
    //chassis.waitUntil(24); //this is how you activate a mechanism midway through a path jerry motion

}

void blue_goal_side(){

    isRedTeam = false; //for color sorting

    //set drivetrain to brake
	chassis.setBrakeMode(pros::E_MOTOR_BRAKE_HOLD);

    //set og pos
    chassis.setPose(0, 0, 270);

    //score alliance
    chassis.swingToHeading(220, DriveSide::LEFT, 500); 
    chassis.moveToPoint(11.5, 6.5, 3000, {.forwards = false, .maxSpeed = 60}); 
    chassis.waitUntilDone();
    runIntake(2000);
    chassis.moveToPoint(0, 6.5, 250, {.forwards = false});

    //grab close goal
    chassis.waitUntilDone();
    chassis.turnToHeading(60, 500);
    chassis.moveToPoint(-36, -13, 2000, {.forwards = false, .maxSpeed = 85});
    chassis.waitUntilDone();
    tilter.set_value(HIGH);
    delay(500);

    //intake colored ring in stack
    chassis.turnToHeading(180, 1000);
    intake.move_velocity(-200);
    chassis.moveToPoint(-30, -40, 4000, {.maxSpeed = 30});
    chassis.waitUntilDone();


}

void blue_stack_side(){

    isRedTeam = false; //for color sorting

    //set drivetrain to brake
	chassis.setBrakeMode(pros::E_MOTOR_BRAKE_HOLD);

    //set og pos
    chassis.setPose(0, 0, 90);

    //score alliance
    chassis.swingToHeading(125, DriveSide::RIGHT, 500);
    chassis.moveToPoint(-8.25, 8.25, 2000, {.forwards = false, .maxSpeed = 60});
    chassis.waitUntilDone();
    runIntake(2000);
    intake.move_velocity(0);
    chassis.moveToPoint(0, 0, 250, {.forwards = false});

    //grab close goal
    chassis.turnToHeading(300, 500);
    chassis.moveToPoint(30, -17, 2000, {.forwards = false, .maxSpeed = 85});
    chassis.waitUntilDone();
    tilter.set_value(HIGH);
    delay(250);

    //get rings haha
    runIntake(3000);
    chassis.moveToPoint(45, -20, 2000);
    chassis.turnToHeading(150, 1000);
    chassis.moveToPoint(49, -28, 2500, {.maxSpeed = 40});
    chassis.turnToHeading(180, 1500);
    chassis.moveToPoint(49.5, -52, 2500, {.maxSpeed = 40});

    //get two stack
    chassis.turnToHeading(270, 700);
    chassis.moveToPoint(25, -47, 2000, {.maxSpeed = 40});
}

void red_goal_side(){

    isRedTeam = true; //for color sorting
    
    //set drivetrain to brake
	chassis.setBrakeMode(pros::E_MOTOR_BRAKE_HOLD);

    //set og pos
    chassis.setPose(0, 0, 90);

    //score alliance
    chassis.swingToHeading(125, DriveSide::RIGHT, 500);
    chassis.moveToPoint(-8.25, 8.3, 2000, {.forwards = false, .maxSpeed = 60});
    chassis.waitUntilDone();
    runIntake(3000);
    chassis.moveToPoint(0, 0, 250, {.forwards = false});

    //grab close goal
    chassis.turnToHeading(300, 500);
    chassis.moveToPoint(27, -19, 2000, {.forwards = false, .maxSpeed = 85});// higher
    chassis.waitUntilDone();
    tilter.set_value(HIGH);
    delay(250);

    //intake colored ring in stack
    chassis.turnToHeading(180, 1000);
    intake.move_velocity(-200);
    chassis.moveToPoint(26, -40, 4000, {.maxSpeed = 30});
    chassis.waitUntilDone();

    //turn around, drop, and touch ladder
    chassis.turnToHeading(0, 1500);
    chassis.waitUntilDone();
    chassis.moveToPoint(33, 1, 3000, {.maxSpeed = 75});
    chassis.waitUntilDone();
    tilter.set_value(LOW);

}

void red_stack_side(){

    isRedTeam = true; //for color sorting

    //set drivetrain to brake
	chassis.setBrakeMode(pros::E_MOTOR_BRAKE_HOLD);

    //set og pos
    chassis.setPose(0, 0, 270);

    //score alliance
    chassis.swingToHeading(220, DriveSide::LEFT, 500); 
    chassis.moveToPoint(11.5, 6.5, 2000, {.forwards = false, .maxSpeed = 60}); 
    chassis.waitUntilDone();
    runIntake(2000);
    chassis.moveToPoint(0, 6.5, 250, {.forwards = false});

    //grab close goal
    chassis.turnToHeading(60, 500);
    chassis.moveToPoint(-36, -16, 2000, {.forwards = false, .maxSpeed = 85});
    chassis.waitUntilDone();
    tilter.set_value(HIGH);
    delay(500);

    //get rings haha
    intake.move_velocity(-200);
    chassis.moveToPoint(-35, -20, 2000);
    chassis.turnToHeading(240, 1000);
    chassis.moveToPoint(-53, -33, 2500, {.maxSpeed = 40});
    chassis.moveToPoint(-53, -53, 2500, {.maxSpeed = 40});

    //get two stack
    chassis.turnToHeading(70, 700);
    chassis.moveToPoint(-22, -40, 2000, {.maxSpeed = 40});
}

// void blue_elims_goal_side(){

// isRedTeam = false;

// }

// void red_elims_goal_side(){
    
// isRedTeam = true;

// }