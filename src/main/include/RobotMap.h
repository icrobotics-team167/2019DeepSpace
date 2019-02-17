#ifndef ROBOT_MAP_H
#define ROBOT_MAP_H

// Pneumatic controller
#define PNEUMATIC_CONTROLLER 2

// ***** Drive Base *****
// Left motor controllers
#define LEFT_TALON_1 3 
#define LEFT_TALON_2 4
#define LEFT_TALON_3 5

// Right motor controllers
#define RIGHT_TALON_1 6
#define RIGHT_TALON_2 7
#define RIGHT_TALON_3 8

// NavX
// Port found automatically

// Limelight
// #define LIMELIGHT

// Gear shifting solenoids
#define LOW_GEAR_SOLENOID 3
#define HIGH_GEAR_SOLENOID 2

// Drivetrain encoders
#define LEFT_ENCODER_A 0
#define LEFT_ENCODER_B 1
#define RIGHT_ENCODER_A 2
#define RIGHT_ENCODER_B 3

// ***** Claw *****
// Claw opening and closing solenoid
#define CLAW_OPEN_SOLENOID 1
#define CLAW_CLOSED_SOLENOID 0

// Claw raising and lowering solenoid
#define PIVOT_SOLENOID 4

// ***** Elevator *****
// Elevator motor
#define ELEVATOR_TALON 9

// Elevator encoder
#define ELEVATOR_ENCODER_A 4
#define ELEVATOR_ENCODER_B 5

// Elevator limit switches
#define ELEVATOR_LIMIT_SWITCH_BOTTOM 6
#define ELEVATOR_LIMIT_SWITCH_MIDDLE 7
#define ELEVATOR_LIMIT_SWITCH_TOP 8

// ***** Bling *****
// Blinkin
#define BLINKIN1 0
#define BLINKIN2 1

// ***** Cargo *****
// Cargo intake
#define CARGO_ARM_TALON 11
#define CARGO_INTAKE_TALON 12 
#define CARGO_LIGHT_SENSOR 3

// Cargo out 
#define CARGO_BACK_OUT_TALON 13
#define CARGO_FRONT_OUT_TALON 14

#endif