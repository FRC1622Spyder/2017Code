#ifndef SRC_INTAKE_H_
#define SRC_INTAKE_H_
#include <CANTalon.h>
#include <Joystick.h>

class Intake {
private:
	Joystick *controlStick;
	CANTalon *intakeMotor; //6
	int IntakeInButton;
	int IntakeOutButton;
	bool intakeForward;
	bool intakeBackward;

public:
	void IntakeInit();
	void RunIntake();
	void IntakeTeleopPeriodic();
};

#endif /* SRC_INTAKE_H_ */
