#ifndef LIMELIGHT_TEST_H
#define LIMELIGHT_TEST_H

#include "Auto/AutoRoutine.h"

class LimelightTest : public AutoRoutine {
private:
    enum class AutoState {
        init, limelightTest, done
    };
    AutoState autoState;
public:
    LimelightTest(DriveBase *driveBase, Claw *claw, Elevator *elevator, Bling *bling, Cargo *cargo);
    ~LimelightTest();
    void run() override;
};

#endif