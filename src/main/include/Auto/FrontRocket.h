#ifndef FRONT_ROCKET_H
#define FRONT_ROCKET_H

#include "Auto/AutoRoutine.h"

class FrontRocket : public AutoRoutine {
private:
    enum class AutoState {
        init, driveOffHAB, turnToRocket, driveCloserToRocket, pointAtRocket, driveToRocket, driveIntoRocket, score, done
    };
    AutoState autoState;
public:
    FrontRocket(DriveBase *driveBase, Claw *claw, Elevator *elevator, Bling *bling, Cargo *cargo, GenericController *controller, Teleop *teleop);
    ~FrontRocket();
    void run() override;
};

#endif