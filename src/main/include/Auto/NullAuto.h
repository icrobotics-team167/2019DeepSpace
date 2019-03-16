#ifndef NULL_AUTO_H
#define NULL_AUTO_H

#include "Auto/AutoRoutine.h"

class NullAuto : public AutoRoutine {
private:
    enum class AutoState {
        init, done
    };
    AutoState autoState;
public:
    NullAuto(DriveBase *driveBase, Claw *claw, Elevator *elevator, Bling *bling, Cargo *cargo, GenericController* controller, Teleop *teleop);
    ~NullAuto();
    void run() override;
};

#endif