#include "Subsystems/Bling.h"

/*
const double SOLID_PINK = 0.57;
const double SOLID_RED = 0.61;
const double SOLID_ORANGE = 0.61;
const double SOLID_GOLD = 0.67;
const double SOLID_YELLOW = 0.69;
const double SOLID_GREEN = 0.77;
const double SOLID_BLUE = 0.87;
const double SOLID_VIOLET = 0.91;
const double SOLID_WHITE = 0.93;
*/

Bling::Bling() {
    // Blinkins
    leftBlinkin = new frc::Spark(LEFT_BLINKIN);
    rightBlinkin = new frc::Spark(RIGHT_BLINKIN);
}

Bling::~Bling() {
    // Blinkins
    delete leftBlinkin; 
    delete rightBlinkin;  
}

void Bling::RunLeftLEDStrip(double pattern) {
    leftBlinkin->Set(pattern);
}

void Bling::RunRightLEDStrip(double pattern) {
    rightBlinkin->Set(pattern);
}