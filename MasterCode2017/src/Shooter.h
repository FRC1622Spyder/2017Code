/*
 * Shooter.h
 *
 *  Created on: Feb 5, 2017
 *      Author: Zack
 */

#ifndef SRC_SHOOTER_H_
#define SRC_SHOOTER_H_
#include <CANTalon.h>
#include <Joystick.h>

class Shooter {

private:
	CANTalon *flywheelMotor;
	Joystick *controlStick;
	bool isSpinning;
	bool buttonPressed;

public:
	void ShooterInit();
	void SpinFlywheel(double power);
	void ShooterTeleopPeriodic();
};

#endif /* SRC_SHOOTER_H_ */
