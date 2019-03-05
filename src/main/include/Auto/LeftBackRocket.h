#ifndef LEFT_BACK_ROCKET_H
#define LEFT_BACK_ROCKET_H

#include "Auto/AutoRoutine.h"

class LeftBackRocket : public AutoRoutine {
private:
    enum class AutoState {
        init, openClaw, driveOffHAB, alignWithBack, driveBack, turnToRocket, driveToRocket, driveIntoRocket, score,
        backOffFromRocket, turnTowardsHumanPlayer, driveToHumanPlayer, driveCloserToHumanPlayer, driveIntoHumanPlayer,
        pickUpHatch, turnToRocketAgain, driveTowardsFrontRocket, driveIntoRocketAgain, scoreAgain, startToRocketAgain, done
    };
    AutoState autoState;
public:
    LeftBackRocket(DriveBase *driveBase, Claw *claw, Elevator *elevator, Bling *bling, Cargo *cargo);
    ~LeftBackRocket();
    void run() override;
};

#endif