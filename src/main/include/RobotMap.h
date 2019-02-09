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
// #define NAVX

// Limelight
// #define LIMELIGHT

// Gear shifting solenoids (these will be replaced with one single-acting solenoid at a later date)
#define LOW_GEAR_SOLENOID 2
#define HIGH_GEAR_SOLENOID 3

// Drivetrain encoders
#define LEFT_ENCODER_A 0
#define LEFT_ENCODER_B 1
#define RIGHT_ENCODER_A 2
#define RIGHT_ENCODER_B 3

// ***** Claw *****
// Claw opening and closing solenoids (these will be replaced with one single-acting solenoid at a later date)
#define CLAW_OPEN_SOLENOID 1
#define CLAW_CLOSED_SOLENOID 0

// Claw raising and lowering solenoid
#define PIVOT_SOLENOID 4 // This port number won't actually work, but it can't conflict with the temporary solenoids described above

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
// LEDs
#define LEFT_LED 9
#define RIGHT_LED 10

// Line-tracking sensors
#define LIGHT_SENSOR_LEFT 0
#define LIGHT_SENSOR_MIDDLE 1
#define LIGHT_SENSOR_RIGHT 2

// ***** Cargo *****
// Cargo intake
#define CARGO_ARM_TALON 11 // Extends and withdraws the cargo arm
#define CARGO_INTAKE_TALON 12 
#define CARGO_LIGHT_SENSOR 3

// Cargo out 
#define CARGO_LEFT_OUT_TALON 13
#define CARGO_RIGHT_OUT_TALON 14

#endif