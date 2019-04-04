#ifndef LEFT_CARGO_SHIP_H
#define LEFT_CARGO_SHIP_H

#include "Auto/AutoRoutine.h"

class LeftCargoShip : public AutoRoutine {
private:
    enum class AutoState {
        init, openClaw, driveOffHAB, driveToCargoShipFront, driveIntoCargoShipFront, /*alignWithCargoShip, checkIsAlignedWithCargoShipFront, driveToCargoShipFront, driveIntoCargoShipFront, */score,
        driveByHumanPlayer, turnTowardsHumanPlayer, driveCloserToHumanPlayer, turnTowardsHumanPlayerAgain, alignWithHumanPlayer, checkIsAlignedWithHumanPlayer,
        driveToHumanPlayer, limelightToPlayer, alignWithHumanPlayerAgain, checkIsAlignedWithHumanPlayerAgain, driveIntoHumanPlayer, pickUpHatch, turnTowardsCargoShip,
        driveCloserToCargoShip, driveCloserToCargoShipAgain, turnTowardsCargoShipAgain, alignWithCargoShipSideAgain, checkIsAlignedWithCargoShipSide, driveToCargoShipSide,
        driveIntoCargoShipSide, scoreAgain, done
    };
    AutoState autoState;
    double cargoShipFrontHeading;
    double cargoShipSideHeading;
    double driveIntoCargoShipFrontInitialHeading;
    double driveToCargoShipFrontInitialHeading;
    double driveByHumanPlayerHeading;
public:
    LeftCargoShip(DriveBase *driveBase, Claw *claw, Elevator *elevator, Bling *bling, Cargo *cargo, GenericController *controller, Teleop *teleop);
    ~LeftCargoShip();
    void run() override;
};

#endif