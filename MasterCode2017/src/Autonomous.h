/*
 * Autonomous.h
 *
 *  Created on: Feb 20, 2017
 *      Author: Zack
 */

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

	const double wheelDiam = WHEEL_DIAM;
	const double driveDiam = DRIVE_DIAM;
	const double pulsePerRev = PULSE_PER_REV;
	const double pi = PI;

	const double pulse_per_inch  = (pulsePerRev) / (wheelDiam * pi); //calculates encoder pulses per inch
	const double pulse_per_radian = (driveDiam / 2) * pulse_per_inch; //calculates encoder pulses per radian

	int autonomousPhase;
	int counter;
	int autonomousChooser;

public:
	void DriveForward(double speed, double distance);
	void DriveBackward(double speed, double distance);
	void RotateClockwise(double speed, double angle);
	void RotateCounterclockwise(double speed, double angle);
	void Wait(double time);
	void AutonomousInit();
	void AutonomousPeriodic();
};

#endif /* SRC_AUTONOMOUS_H_ */
