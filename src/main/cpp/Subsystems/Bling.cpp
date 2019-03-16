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

void Bling::runBothLEDStrips(double pattern) {
    runLeftLEDStrip(pattern);
    runRightLEDStrip(pattern);
}

void Bling::runLeftLEDStrip(double pattern) {
    leftBlinkin->Set(pattern);
}

void Bling::runRightLEDStrip(double pattern) {
    rightBlinkin->Set(pattern);
}

