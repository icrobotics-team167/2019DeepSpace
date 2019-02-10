#ifndef ENCODER_TEST_H
#define ENCODER_TEST_H

#include "Auto/AutoRoutine.h"

class EncoderTest : public AutoRoutine {
private:
    enum class AutoState {
        init, test
    };
    AutoState autoState;

    frc::Encoder *leftEncoder;
    frc::Encoder *rightEncoder;
public:
    EncoderTest(DriveBase *driveBase, Claw *claw, Elevator *elevator, Bling *bling, Cargo *cargo);
    ~EncoderTest();
    void run() override;
};

#endif