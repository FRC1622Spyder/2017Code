#include <iostream>
#include <memory>
#include <string>

#include <IterativeRobot.h>
#include <Joystick.h>
#include <CANTalon.h>
#include <Drive.h>
#include <LiveWindow/LiveWindow.h>
#include <SmartDashboard/SendableChooser.h>
#include <SmartDashboard/SmartDashboard.h>

void Drive::DriveInit() {
	//declares a joystick / which will be used for driving / uses port zero
	driveStick = new Joystick(0);
	//declares the motors / for all sides of the robot / three, four, one, and two 
	leftBackMotor = new CANTalon(4);
	leftFrontMotor = new CANTalon(3);
	rightBackMotor = new CANTalon(2);
	rightFrontMotor = new CANTalon(1);
	//inverts the left side / so that the robot drives straight / or else it will spin 
	leftBackMotor->SetInverted(true);
	leftFrontMotor->SetInverted(true);
	//adds QuadEncoders / to track motor position / on both of the sides 
	leftFrontMotor->SetFeedbackDevice(CANTalon::QuadEncoder);
	rightFrontMotor->SetFeedbackDevice(CANTalon::QuadEncoder);

	speedValueLeft = 0.0;
	speedValueRight = 0.0;
}
//this is a function / that drives the left side motors / it uses doubles 
void Drive::DriveLeft(double speed){
	leftFrontMotor->Set(speed);
	leftBackMotor->Set(speed);
}

//another function / but drives right motors instead / doubles used, also 
void Drive::DriveRight(double speed){
	rightFrontMotor->Set(speed);
	rightBackMotor->Set(speed);
}

void Drive::DriveTeleopPeriodic() {
	//this is a toggle / so robot drives at half speed / 'cuz it's more exact 
	bool toggleButton = driveStick->GetRawButton(2);
	if(toggleButton == true && buttonPressed == false && halfSpeed == false){
		halfSpeed = true;
		buttonPressed = true;
	}
	else if(toggleButton == true && buttonPressed == false && halfSpeed == true){
		halfSpeed = false;
		buttonPressed = true;
	}

	if(toggleButton == false){
		buttonPressed = false;	
	}

	//gets left joystick speed / to make robot start driving / from the left axis
	double leftSpeed = driveStick->GetRawAxis(1);
	if(halfSpeed == true){
		leftSpeed = leftSpeed / 2;
	}
	//if driving forward / and speed is above point eight / and above point one 
	//set maximum speed / to a value of point eight / burning motors sucks 
	if(leftSpeed > 0.1 && leftSpeed > 0.8){
		leftSpeed = 0.8;
	}
	//if driving forward / but speed is below point five / and outside dead zone
	//divide speed by two / to provide better control / so we don't hit things
	else if(leftSpeed >= 0.1 && leftSpeed <= 0.5){
		leftSpeed = leftSpeed / 2;
	}
	//if driving backward / with a speed above point eight / and not in dead zone
	//set maximum speed / with magnitude of point eight / not magnitude one
	else if(leftSpeed < -0.1 && leftSpeed < -0.8){
		leftSpeed = -0.8;
	}
	//if driving backward / and outside of the dead zone / and below point five
	//multiply by half / so we don't crash the robot / by driving too fast
	else if(leftSpeed <= -0.1 && leftSpeed >= -0.5){
		leftSpeed = leftSpeed / 2;
	}
	//if speed in dead zone / speed should be set to zero / in case joystick drifts
	else if(leftSpeed > -0.1 && leftSpeed < 0.1){
		leftSpeed = 0;
	}
	//gets left joystick speed / to make robot start driving / from the left axis
	double rightSpeed = driveStick->GetRawAxis(3);
	if(halfSpeed == true){
		rightSpeed = rightSpeed / 2;
	}
	//if driving forward / and speed is above point eight / and above point one 
	//set maximum speed / to a value of point eight / burning motors sucks 
	if(rightSpeed > 0.1 && rightSpeed > 0.8){
		rightSpeed = 0.8;
	}
	//if driving forward / but speed is below point five / and outside dead zone
	//divide speed by two / to provide better control / so we don't hit things
	else if(rightSpeed >= 0.1 && rightSpeed <= 0.5){
		rightSpeed = rightSpeed / 2;
	}
	//if driving backward / with a speed above point eight / and not in dead zone
	//set maximum speed / with magnitude of point eight / not magnitude one
	else if(rightSpeed < -0.1 && rightSpeed < -0.8){
		rightSpeed = -0.8;
	}
	//if driving backward / and outside of the dead zone / and below point five
	//multiply by half / so we don't crash the robot / by driving too fast
	else if(rightSpeed <= -0.1 && rightSpeed >= -0.5){
		rightSpeed = rightSpeed / 2;
	}
	//if speed in dead zone / speed should be set to zero / in case joystick drifts
	else if(rightSpeed > -0.1 && rightSpeed < 0.1){
		rightSpeed = 0;
	}
	//drive the robot / with modified speed values / post-calculations
	DriveLeft(leftSpeed);
	DriveRight(rightSpeed);
}

void Drive::DriveAutomatic(){
	drive = driveStick->GetRawButton(6);
	if(drive == true && wasDriving == false && isDriving == false){
		isDriving = true;
		wasDriving = true;
	}

	if(drive == false){
		wasDriving = false;
	}

	if(isDriving == true){
		if(drivePhase == 0){
			double encoderValue = leftFrontMotor->GetEncPosition();
			double encoderDistance = 30.0 * pulse_per_inch;
			if(abs(encoderValue) <= encoderDistance){
				leftFrontMotor->Set(0.6);
				leftBackMotor->Set(0.6);
				rightFrontMotor->Set(0.6);
				rightBackMotor->Set(0.6);
			}
			else {
				leftFrontMotor->Set(0.0);
				leftBackMotor->Set(0.0);
				rightFrontMotor->Set(0.0);
				rightBackMotor->Set(0.0);
				leftFrontMotor->SetEncPosition(0);
				rightFrontMotor->SetEncPosition(0);
				drivePhase++;
			}
		}
		else if(drivePhase == 1){
			isDriving = false;
			drivePhase = 0;
		}
	}
}
