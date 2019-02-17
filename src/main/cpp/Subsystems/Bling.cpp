#include "Subsystems/Bling.h"

Bling::Bling() {
    // Blinkin
    blinkin1 = new frc::Spark(BLINKIN1);
    blinkin2 = new frc::Spark(BLINKIN2);

    double patternVal;
}

Bling::~Bling() {
    // Blinkin
    delete blinkin1;
    delete blinkin2;   
}

void Bling::RunLEDStrip1(double pattern) {
    blinkin1->Set(pattern);
}

void Bling::RunLEDStrip2(double pattern) {
    blinkin2->Set(pattern);
}