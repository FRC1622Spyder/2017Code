#ifndef SRC_SHOOTER_H_
#define SRC_SHOOTER_H_
#include <CANTalon.h>
#include <Joystick.h>
#include <DriverStation.h>

class Shooter {

private:
	CANTalon *flywheelMotor;
	Joystick *controlStick;
	int ShooterToggle;
	int IncreaseSpeed;
	int DecreaseSpeed;
	bool isSpinning;
	bool togglePressed;
	bool upPressed;
	bool downPressed;
	int flywheelSpeed;

public:
	void ShooterInit();
	void SpinFlywheel();
	void ShooterTeleopPeriodic();
};

#endif /* SRC_SHOOTER_H_ */
