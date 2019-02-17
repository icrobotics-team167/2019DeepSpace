#ifndef BACK_ROCKET_H
#define BACK_ROCKET_H

#include "Auto/AutoRoutine.h"

class BackRocket : public AutoRoutine {
private:
    enum class AutoState {
        init, driveOffHAB, alignWithBack, driveBack, turnToRocket, driveToRocket, driveIntoRocket, score, done
    };
    AutoState autoState;
public:
    BackRocket(DriveBase *driveBase, Claw *claw, Elevator *elevator, Bling *bling, Cargo *cargo);
    ~BackRocket();
    void run() override;
};

#endif