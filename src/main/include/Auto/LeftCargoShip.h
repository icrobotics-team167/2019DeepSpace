#ifndef LEFT_CARGO_SHIP_H
#define LEFT_CARGO_SHIP_H

#include "Auto/AutoRoutine.h"

class LeftCargoShip : public AutoRoutine {
private:
    enum class AutoState {
        init, openClaw, driveOffHAB, alignWithCargoShip, driveToCargoShipFront, driveIntoCargoShipFront, score,
        turnTowardsHumanPlayer, driveCloserToHumanPlayer, turnTowardsHumanPlayerAgain,
        driveToHumanPlayer, driveIntoHumanPlayer, pickUpHatch, turnTowardsCargoShip,
        driveCloserToCargoShip, turnTowardsCargoShipAgain, driveToCargoShipSide,
        driveIntoCargoShipSide, scoreAgain, done
    };
    AutoState autoState;
public:
    LeftCargoShip(DriveBase *driveBase, Claw *claw, Elevator *elevator, Bling *bling, Cargo *cargo, GenericController *controller, Teleop *teleop);
    ~LeftCargoShip();
    void run() override;
};

#endif