#ifndef RIGHT_CARGO_SHIP_H
#define RIGHT_CARGO_SHIP_H

#include "Auto/AutoRoutine.h"

class RightCargoShip : public AutoRoutine {
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
    RightCargoShip(DriveBase *driveBase, Claw *claw, Elevator *elevator, Bling *bling, Cargo *cargo, GenericController *controller);
    ~RightCargoShip();
    void run() override;
};

#endif