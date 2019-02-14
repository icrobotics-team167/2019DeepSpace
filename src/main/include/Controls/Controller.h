#ifndef CONTROLLER_H
#define CONTROLLER_H

class Controller {
    private:
        
    public:
        virtual double getDrivetrainLeftSpeed();
        virtual double getDrivetrainRightSpeed();
        virtual bool getOpenClaw();
        virtual bool getCloseClaw();
        virtual bool getSetHighGear();
        virtual bool getSetLowGear();
        virtual bool getRaiseClaw();
        virtual bool getLowerClaw();
        virtual bool getRaiseElevator();
        virtual bool getLowerElevator();
        virtual bool getRunFrontOut();
        virtual bool getRunBackOut();
        virtual bool getRunIntake();
};

#endif