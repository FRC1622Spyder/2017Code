//please enjoy our code
//it's written all in haiku
//wait, just the comments

//the first line has five / the second line has seven / the third line has five

#ifndef SRC_AUTONOMOUS_H_
#define SRC_AUTONOMOUS_H_

#define WHEEL_DIAM 6.0;
#define DRIVE_DIAM 28.75;
#define PULSE_PER_REV 860.0;
#define PI 3.141593;

class Autonomous {
private:
	CANTalon *leftBackMotor;
	CANTalon *leftFrontMotor;
	CANTalon *rightBackMotor;
	CANTalon *rightFrontMotor;

	CANTalon *shooterMotor;
	CANTalon *feederMotor;

	const double wheelDiam = WHEEL_DIAM;
	const double driveDiam = DRIVE_DIAM;
	const double pulsePerRev = PULSE_PER_REV;
	const double pi = PI;

	const double pulse_per_inch  = (pulsePerRev) / (wheelDiam * pi);
	const double pulse_per_radian = (driveDiam / 2) * pulse_per_inch;

	int autonomousPhase;
	int counter;
	int autonomousChooser;

public:
	void DriveForward(double speed, double distance);
	void DriveBackward(double speed, double distance);
	void RotateClockwise(double speed, double angle);
	void RotateCounterclockwise(double speed, double angle);
	void Shoot(double speed, double time);
	void Wait(double time);
	void AutonomousInit();
	void AutonomousPeriodic();
};

#endif /* SRC_AUTONOMOUS_H_ */
