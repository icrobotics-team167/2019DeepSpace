#include "Subsystems/Bling.h"

Bling::Bling() {
    // Blinkin
    blinkin = new frc::Spark(BLINKIN);

    double patternVal;
}

Bling::~Bling() {
    // Blinkin
    delete blinkin;   
}

Bling::RunLEDStrip(double pattern) {
    blinkin->Set(pattern);
}