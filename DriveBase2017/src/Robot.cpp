#include <iostream>
#include <memory>
#include <string>

#include <IterativeRobot.h>
#include <Joystick.h>
#include <CANTalon.h>
#include <LiveWindow/LiveWindow.h>
#include <SmartDashboard/SendableChooser.h>
#include <SmartDashboard/SmartDashboard.h>

class Robot:public IterativeRobot {

private:

	Joystick *driveStick = new Joystick(0); //Declare joystick and motors
	CANTalon *leftBackMotor = new CANTalon(9);
	CANTalon *leftFrontMotor = new CANTalon(6);
	CANTalon *rightBackMotor = new CANTalon(7);
	CANTalon *rightFrontMotor = new CANTalon(8);

	double speedValueLeft = 0.0; //Declare current speed
	double speedValueRight = 0.0;

	//double leftPast = 0.0; //Ramp code - removed because it's currently unused
	//double rightPast = 0.0;

	/*double accelerateLeft(double maxSpeed) {
		//std::cout << "LeftStick: " << maxSpeed << std::endl;
		if(maxSpeed >= 0.0 && leftPast >= 0.0){
			leftPast = maxSpeed;
		}
		else if(maxSpeed <= 0.0 && leftPast <= 0.0){
			leftPast = maxSpeed;
		}
		else{
			leftPast = maxSpeed;
			speedValueLeft = 0.0;
			return speedValueLeft;
		}

		if(maxSpeed > 0.2){
			speedValueLeft += 0.05;
			if(speedValueLeft < maxSpeed){
				if(speedValueLeft < 0.8){
					return speedValueLeft;
				}
				else{
					return 0.8;
				}
			}
			else {
				return maxSpeed;
			}
		}
		else if(maxSpeed < -0.2){
			speedValueLeft -= 0.05;
			if(speedValueLeft > maxSpeed){
				if(speedValueLeft > -0.8){
					return speedValueLeft;
				}
				else{
					return -0.8;
				}
			}
			else {
				return maxSpeed;
			}
		}
		else{
			speedValueLeft=0.0;
			return speedValueLeft;
		}
	}

	double accelerateRight(double maxSpeed) {
		//std::cout << "RightStick: " << maxSpeed << std::endl;
		if(maxSpeed >= 0.0 && rightPast >= 0.0){
			rightPast = maxSpeed;
		}
		else if(maxSpeed <= 0.0 && rightPast <= 0.0){
			rightPast = maxSpeed;
		}
		else{
			rightPast = maxSpeed;
			speedValueRight = 0.0;
			return speedValueRight;
		}

		if(maxSpeed > 0.2){
			speedValueRight += 0.05;
			if(speedValueRight < maxSpeed){
				if(speedValueRight < 0.8){
					return speedValueRight;
				}
				else{
					return 0.8;
				}
			}
			else {
				return maxSpeed;
			}
		}
		else if(maxSpeed < -0.2){
			speedValueRight -= 0.05;
			if(speedValueRight > maxSpeed){
				if(speedValueRight > -0.8){
					return speedValueRight;
				}
				else{
					return -0.8;
				}
			}
			else {
				return maxSpeed;
			}
		}
		else{
			speedValueRight = 0.0;
			return speedValueRight;
		}
	}*/

	void driveLeft(double speed){ //Drives left motors
		leftFrontMotor->Set(speed);
		leftBackMotor->Set(speed);
	}

	void driveRight(double speed){ //Drives right motors
		rightFrontMotor->Set(speed);
		rightBackMotor->Set(speed);
	}

	/*void driveRobot(){ //Ramp code
		double leftStick = driveStick->GetRawAxis(1);
		double rightStick = driveStick->GetRawAxis(3);
		driveLeft(accelerateLeft(leftStick));
		driveRight(accelerateRight(rightStick));
	}*/

	void RobotInit() {
		leftBackMotor->SetInverted(true); //Inverts left motors
		leftFrontMotor->SetInverted(true);
	}

	void AutonomousInit() {
	}

	void AutonomousPeriodic() {
	}

	void TeleopInit() {
	}

	void TeleopPeriodic() {
		//driveRobot(); //Ramp code
		double leftSpeed = driveStick->GetRawAxis(1); //Get left joystick
		if(leftSpeed > 0.2 && leftSpeed > 0.8){ //If speed is positive, outside dead zone, and above 80% (set to max speed)
			leftSpeed = 0.8;
		}
		else if(leftSpeed >= 0.2 && leftSpeed <= 0.5){ //If speed is positive, outside dead zone, and below 50% (set to half speed)
			leftSpeed = leftSpeed / 2;
		}
		else if(leftSpeed < -0.2 && leftSpeed < -0.8){ //If speed is negative, outside dead zone, and below -80% (set to max speed)
			leftSpeed = -0.8;
		}
		else if(leftSpeed <= -0.2 && leftSpeed >= -0.5){ //If speed is negative, outside dead zone, and above -50% (set to half speed)
			leftSpeed = leftSpeed / 2;
		}
		else if(leftSpeed > -0.2 && leftSpeed < 0.2){ //If speed is in dead zone (set to 0)
			leftSpeed = 0;
		}
		double rightSpeed = driveStick->GetRawAxis(3); //Get right joystick
		if(rightSpeed > 0.2 && rightSpeed > 0.8){ //If speed is positive, outside dead zone, and above 80% (set to max speed)
			rightSpeed = 0.8;
		}
		else if(rightSpeed >= 0.2 && rightSpeed <= 0.5){ //If speed is positive, outside dead zone, and below 50% (set to half speed)
			rightSpeed = rightSpeed / 2;
		}
		else if(rightSpeed < -0.2 && rightSpeed < -0.8){ //If speed is negative, outside dead zone, and below -80% (set to max speed)
			rightSpeed = -0.8;
		}
		else if(rightSpeed <= -0.2 && rightSpeed >= -0.5){ //If speed is negative, outside dead zone, and above -50% (set to half speed)
			rightSpeed = rightSpeed / 2;
		}
		else if(rightSpeed > -0.2 && rightSpeed < 0.2){ //If speed is in dead zone (set to 0)
			rightSpeed = 0;
		}
		driveLeft(leftSpeed);
		driveRight(rightSpeed);
	}

	void TestPeriodic() {
	}
};

START_ROBOT_CLASS(Robot)
