#ifndef LEFT_CARGO_SHIP_H
#define LEFT_CARGO_SHIP_H

#include "Auto/AutoRoutine.h"

class LeftCargoShip : public AutoRoutine {
private:
    enum class AutoState {
        init, openClaw, driveOffHAB, driveToCargoShipFront, driveIntoCargoShipFront, /*alignWithCargoShip, checkIsAlignedWithCargoShipFront, driveToCargoShipFront, driveIntoCargoShipFront, */score,
        turnTowardsHumanPlayer, driveCloserToHumanPlayer, turnTowardsHumanPlayerAgain, alignWithHumanPlayer, checkIsAlignedWithHumanPlayer,
        driveToHumanPlayer, limelightToPlayer, alignWithHumanPlayerAgain, checkIsAlignedWithHumanPlayerAgain, driveIntoHumanPlayer, pickUpHatch, turnTowardsCargoShip,
        driveCloserToCargoShip, turnTowardsCargoShipAgain, alignWithCargoShipSideAgain, checkIsAlignedWithCargoShipSide, driveToCargoShipSide,
        driveIntoCargoShipSide, scoreAgain, done
    };
    AutoState autoState;
    double cargoShipSideHeading;
public:
    LeftCargoShip(DriveBase *driveBase, Claw *claw, Elevator *elevator, Bling *bling, Cargo *cargo, GenericController *controller, Teleop *teleop);
    ~LeftCargoShip();
    void run() override;
};

#endif