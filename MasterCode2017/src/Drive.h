#ifndef SRC_DRIVE_H_
#define SRC_DRIVE_H_
#include <Joystick.h>
#include <CANTalon.h>

#define WHEEL_DIAM 6.0;
#define PULSE_PER_REV 860.0;
#define PI 3.141593;

class Drive {

private:
	Joystick *driveStick;
	CANTalon *leftBackMotor;
	CANTalon *leftFrontMotor;
	CANTalon *rightBackMotor;
	CANTalon *rightFrontMotor;

	const double wheelDiam = WHEEL_DIAM;
	const double pulsePerRev = PULSE_PER_REV;
	const double pi = PI;

	const double pulse_per_inch  = (pulsePerRev) / (wheelDiam * pi);

	double speedValueLeft = 0.0;
	double speedValueRight = 0.0;

	bool buttonPressed = false;
	bool halfSpeed = false;

	bool drive = false;
	bool wasDriving = false;
	bool isDriving = false;
	int drivePhase = 0;

public:
	void DriveInit();
	void DriveLeft(double speed);
	void DriveRight(double speed);
	void DriveTeleopPeriodic();
	void DriveAutomatic();
};

#endif /* SRC_DRIVE_H_ */
