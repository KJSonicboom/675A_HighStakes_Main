#include "main.h"
#include "lemlib/api.hpp" // IWYU pragma: keep

//robodash stuff for auton selector
rd::Selector selector({
   {"Blue Goal Side", &blue_goal_side},
   {"Blue Stack Side", &blue_stack_side},
   {"Red Goal Side", &red_goal_side},
   {"Red Stack Side", &red_stack_side}
});

rd::Console console;

void initialize() {

	selector.focus();

	chassis.calibrate(); // calibrate sensors
	pros::Task screenTask([&]() {
        while (true) {
            // print robot location to the brain screen
            console.printf("X: %f", chassis.getPose().x); // x
            console.printf("Y: %f", chassis.getPose().y); // y
            console.printf("Theta: %f", chassis.getPose().theta); // heading
            // log position telemetry
            lemlib::telemetrySink()->info("Chassis pose: {}", chassis.getPose());
            // delay to save resources
            pros::delay(50);
        }
    });

}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize() {

	selector.focus(); //needs to be tested
}

/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */
void autonomous() {

	selector.run_auton();

    chassis.moveToPoint(10, 0, 5);
    chassis.waitUntilDone();
    

}

/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */
void opcontrol() {

	console.println("Op control running..."); //robodash testing

    selector.run_auton(); //for testing purposes

	Task iLoveRings(eatRings, "yummy");
	Task drive(arcade_flipped, "vrrrr");
	Task wallStakes(lift, "wallStakes");
	Task mogos(holdTilter, "holdOnToThese-");
	Task macroWalls(liftMacro, "headTop");
	Task doink(doinking, "DOINK what a funny word");
	Task intakeMove(elevateIntake, "eat more rings"); //comment out before match
	//Task yum(eat, "just yum"); <--- manual intake control just in case

}