#include "Subsystems/Bling.h"

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