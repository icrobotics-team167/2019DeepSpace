#ifndef LEFT_CARGO_SHIP_V2_H
#define LEFT_CARGO_SHIP_V2_H

#include "Auto/AutoRoutine.h"

class LeftCargoShipV2 : public AutoRoutine {
private:
    enum class AutoState {
        init, openClaw, driveOffHAB, driveToCargoShipFront, driveIntoCargoShipFront, score,
        driveCloserToHumanPlayer, turnTowardsHumanPlayerAgain, driveToHumanPlayer, driveIntoHumanPlayer, 
        pickUpHatch, driveCloserToCargoShip, turnTowardsCargoShipAgain, driveToCargoShipSide,
        driveIntoCargoShipSide, scoreAgain, done
    };
    AutoState autoState;
public:
    LeftCargoShipV2(DriveBase *driveBase, Claw *claw, Elevator *elevator, Bling *bling, Cargo *cargo, GenericController *controller, Teleop *teleop);
    ~LeftCargoShipV2();
    void run() override;
};

#endif