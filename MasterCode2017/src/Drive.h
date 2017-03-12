#ifndef SRC_DRIVE_H_
#define SRC_DRIVE_H_
#include <Joystick.h>
#include <CANTalon.h>

class Drive {

private:
	Joystick *driveStick;
	CANTalon *leftBackMotor;
	CANTalon *leftFrontMotor;
	CANTalon *rightBackMotor;
	CANTalon *rightFrontMotor;
	int LeftAxis;
	int RightAxis;
	int SpeedToggle;
	double speedValueLeft = 0.0;
	double speedValueRight = 0.0;
	bool buttonPressed = false;
	bool halfSpeed = false;

public:
	void DriveInit();
	void DriveLeft(double speed);
	void DriveRight(double speed);
	void DriveTeleopPeriodic();
};

#endif /* SRC_DRIVE_H_ */
