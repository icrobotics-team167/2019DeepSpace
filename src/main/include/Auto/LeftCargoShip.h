#ifndef LEFT_CARGO_SHIP_H
#define LEFT_CARGO_SHIP_H

#include "Auto/AutoRoutine.h"

class LeftCargoShip : public AutoRoutine {
private:
    enum class AutoState {
        init, openClaw, driveOffHAB, alignWithCargoShip, checkIsAlignedWithCargoShipFront, driveToCargoShipFront, driveIntoCargoShipFront, score,
        turnTowardsHumanPlayer, driveCloserToHumanPlayer, turnTowardsHumanPlayerAgain, alignWithHumanPlayer, checkIsAlignedWithHumanPlayer,
        driveToHumanPlayer, limelightToPlayer, alignWithHumanPlayerAgain, driveIntoHumanPlayer, pickUpHatch, turnTowardsCargoShip,
        driveCloserToCargoShip, turnTowardsCargoShipAgain, alignWithCargoShipSideAgain, driveToCargoShipSide,
        driveIntoCargoShipSide, scoreAgain, done
    };
    AutoState autoState;
public:
    LeftCargoShip(DriveBase *driveBase, Claw *claw, Elevator *elevator, Bling *bling, Cargo *cargo, GenericController *controller, Teleop *teleop);
    ~LeftCargoShip();
    void run() override;
};

#endif