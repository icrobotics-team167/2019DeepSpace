#ifndef AUTO_TEST_H
#define AUTO_TEST_H

#include "Auto/AutoRoutine.h"

class AutoTest : public AutoRoutine {
private:
    enum class AutoState {
        init, drive100, turn180, done
    };
    AutoState autoState;

    frc::Encoder *leftEncoder;
    frc::Encoder *rightEncoder;
public:
    AutoTest(DriveBase *driveBase, Claw *claw, Elevator *elevator, Bling *bling, Cargo *cargo);
    ~AutoTest();
    void run() override;
};

#endif