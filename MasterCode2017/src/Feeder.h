#ifndef SRC_FEEDER_H_
#define SRC_FEEDER_H_
#include <CANTalon.h>
#include <Joystick.h>
#include <IterativeRobot.h>

class Feeder {

private:
	CANTalon *feederMotor;
	Joystick *controlStick;
	bool isWorking;
	bool buttonPressed;

public:
	void FeederInit();
	void FeederTeleopPeriodic();
};

#endif /* SRC_FEEDER_H_ */
