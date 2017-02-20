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
	driveStick = new Joystick(0);
	leftBackMotor = new CANTalon(3);//8 on the test robot, 3 on actual robot
	leftFrontMotor = new CANTalon(4);
	rightBackMotor = new CANTalon(1);
	rightFrontMotor = new CANTalon(2);

	leftBackMotor->SetInverted(true);
	leftFrontMotor->SetInverted(true);

	leftFrontMotor->SetFeedbackDevice(CANTalon::QuadEncoder);
	rightFrontMotor->SetFeedbackDevice(CANTalon::QuadEncoder);

	speedValueLeft = 0.0;
	speedValueRight = 0.0;
}
//Drives left motors
void Drive::DriveLeft(double speed){
	leftFrontMotor->Set(speed);
	leftBackMotor->Set(speed);
}

//Drives right motors
void Drive::DriveRight(double speed){
	rightFrontMotor->Set(speed);
	rightBackMotor->Set(speed);
}

void Drive::DriveTeleopPeriodic() {
	//driveRobot(); //Ramp code
	bool toggleButton = driveStick->GetRawButton(3); //change that number later
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
	//Get left joystick
	double leftSpeed = driveStick->GetRawAxis(1);
	if(halfSpeed == true){
		leftSpeed = leftSpeed / 2;
	}
	//If speed is positive, outside dead zone, and above 80% (set to max speed)
	if(leftSpeed > 0.1 && leftSpeed > 0.8){
		leftSpeed = 0.8;
	}
	//If speed is positive, outside dead zone, and below 50% (set to half speed)
	else if(leftSpeed >= 0.1 && leftSpeed <= 0.5){
		leftSpeed = leftSpeed / 2;
	}
	//If speed is negative, outside dead zone, and below -80% (set to max speed)
	else if(leftSpeed < -0.1 && leftSpeed < -0.8){
		leftSpeed = -0.8;
	}
	//If speed is negative, outside dead zone, and above -50% (set to half speed)
	else if(leftSpeed <= -0.1 && leftSpeed >= -0.5){
		leftSpeed = leftSpeed / 2;
	}
	//If speed is in dead zone (set to 0)
	else if(leftSpeed > -0.1 && leftSpeed < 0.1){
		leftSpeed = 0;
	}
	//Get right joystick
	double rightSpeed = driveStick->GetRawAxis(3);
	if(halfSpeed == true){
		rightSpeed = rightSpeed / 2;
	}
	//If speed is positive, outside dead zone, and above 80% (set to max speed)
	if(rightSpeed > 0.1 && rightSpeed > 0.8){
		rightSpeed = 0.8;
	}
	//If speed is positive, outside dead zone, and below 50% (set to half speed)
	else if(rightSpeed >= 0.1 && rightSpeed <= 0.5){
		rightSpeed = rightSpeed / 2;
	}
	//If speed is negative, outside dead zone, and below -80% (set to max speed)
	else if(rightSpeed < -0.1 && rightSpeed < -0.8){
		rightSpeed = -0.8;
	}
	//If speed is negative, outside dead zone, and above -50% (set to half speed)
	else if(rightSpeed <= -0.1 && rightSpeed >= -0.5){
		rightSpeed = rightSpeed / 2;
	}
	//If speed is in dead zone (set to 0)
	else if(rightSpeed > -0.1 && rightSpeed < 0.1){
		rightSpeed = 0;
	}
	//Drive the robot
	DriveLeft(leftSpeed);
	DriveRight(rightSpeed);
}
