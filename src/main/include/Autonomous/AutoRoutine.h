#ifndef AUTO_ROUTINE_H
#define AUTO_ROUTINE_H

#include "Robot.h"

/**
 * Interface for auto routines.
 * 
 * @author Dominic Rutkowski
 * @since 2-10-2019
 * 
 * @field *robot Pointer to access robot subsystems
 * @field AutoState Enum class of states in this auto routine
 * @field autoState The current auto state
 * 
 * @constructor AutoRoutine The speed that the right motor group will drive at
 * @method run Event loop for this auto routine
 */ 
class AutoRoutine {
private:
    Robot *robot;
    enum class AutoState;
    AutoState autoState;
public:
    AutoRoutine(Robot *robot);
    virtual void run();
};

#endif