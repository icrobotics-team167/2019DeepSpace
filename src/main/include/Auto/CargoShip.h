#ifndef CARGO_SHIP_H
#define CARGO_SHIP_H

#include "Auto/AutoRoutine.h"

class CargoShip : public AutoRoutine {
private:
    enum class AutoState {
        init, openClaw, driveOffHAB, driveToCargoShipFront, driveIntoCargoShipFront, score,
        turnTowardsHumanPlayer, driveCloserToHumanPlayer, turnTowardsHumanPlayerAgain,
        driveToHumanPlayer, driveIntoHumanPlayer, pickUpHatch, turnTowardsCargoShip,
        driveCloserToCargoShip, turnTowardsCargoShipAgain, driveToCargoShipSide,
        driveIntoCargoShipSide, scoreAgain, done
    };
    AutoState autoState;
public:
    CargoShip(DriveBase *driveBase, Claw *claw, Elevator *elevator, Bling *bling, Cargo *cargo);
    ~CargoShip();
    void run() override;
};

#endif