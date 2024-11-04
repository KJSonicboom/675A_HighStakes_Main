#include "main.h"
#include "lemlib/api.hpp" // IWYU pragma: keep

//robodash stuff for auton selector
rd::Selector selector({
   {"Blue Goal Side", &blue_goal_side},
   {"Blue Stack Side", &blue_stack_side},
   {"Red Goal Side", &red_goal_side},
   {"Red Stack Side", &red_stack_side}
});

//robodash console
rd::Console console;

void initialize() {

	chassis.calibrate(); // calibrate sensors
	pros::Task screenTask([&]() {
        while (true) {
            // print robot location to the brain screen (not right))
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


void disabled() {}


void competition_initialize() {

	selector.focus(); //needs to be tested
}


void autonomous() {

	// selector.run_auton();

    pathJerryTest(); //path jerry test run

}

void opcontrol() {

	console.println("Op control running..."); //robodash testing

	// Task iLoveRings(eatRings, "yummy");
	Task drive(arcade_flipped, "vrrrr");
	Task wallStakes(lift, "wallStakes");
	Task mogos(holdTilter, "holdOnToThese-");
	Task macroWalls(liftMacro, "headTop");
	Task doink(doinking, "DOINK what a funny word");
	// Task intakeMove(elevateIntake, "eat more rings"); // <---- intake piston
	Task yum(eat, "just yum"); 
}