#ifndef RIGHT_BACK_ROCKET_H
#define RIGHT_BACK_ROCKET_H

#include "Auto/AutoRoutine.h"

class RightBackRocket : public AutoRoutine {
private:
    enum class AutoState {
        init, openClaw, driveOffHAB, alignWithBack, driveBack, turnToRocket, driveToRocket, driveIntoRocket, score,
        backOffFromRocket, turnTowardsHumanPlayer, teleop, driveToHumanPlayer, driveCloserToHumanPlayer, driveIntoHumanPlayer,
        pickUpHatch, turnToRocketAgain, driveTowardsFrontRocket, driveIntoRocketAgain, scoreAgain, startToRocketAgain, done
    };
    AutoState autoState;
public:
    RightBackRocket(DriveBase *driveBase, Claw *claw, Elevator *elevator, Bling *bling, Cargo *cargo, GenericController *controller, Teleop *teleop);
    ~RightBackRocket();
    void run() override;
};

#endif