#ifndef SRC_CLIMBER_H_
#define SRC_CLIMBER_H_
#include <CANTalon.h>
#include <Joystick.h>

class Climber {

private:
	CANTalon *ClimberMotor;
	Joystick *controlStick;
	int climberButton;
	bool isWorking;
	bool buttonPressed;
	bool climbDirection;

public:
	void ClimberInit();
	void ClimberTeleopPeriodic();
};

#endif /* SRC_CLIMBER_H_ */
