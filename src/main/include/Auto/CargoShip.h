#ifndef CARGO_SHIP_H
#define CARGO_SHIP_H

#include "Auto/AutoRoutine.h"

class CargoShip : public AutoRoutine {
private:
    enum class AutoState {
        init, openClaw, driveToCargoShipFront, driveIntoCargoShipFront, score,
        turnTowardsHumanPlayer, driveCloserToHumanPlayer, turnTowardsHumanPlayerAgain,
        driveToHumanPlayer, driveIntoHumanPlayer, pickUpHatch, turn180, driveFromHumanPlayer,
        turnTowardsCargoShip, driveCloserToCargoShip, turnTowardsCargoShipAgain, driveToCargoShipSide,
        driveIntoCargoShipSide, scoreAgain, done
    };
    AutoState autoState;
public:
    CargoShip(DriveBase *driveBase, Claw *claw, Elevator *elevator, Bling *bling, Cargo *cargo);
    ~CargoShip();
    void run() override;
};

#endif