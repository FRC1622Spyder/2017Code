#include <iostream>
#include <memory>
#include <string>
#include <math.h>

#include <IterativeRobot.h>
#include <CANTalon.h>
#include <Encoder.h>
#include <Timer.h>
#include <LiveWindow/LiveWindow.h>
#include <SmartDashboard/SendableChooser.h>
#include <SmartDashboard/SmartDashboard.h>

#define WHEEL_DIAM 6.0;
#define DRIVE_DIAM 28.75;
#define PULSE_PER_REV 860.0;
#define DEGREES_PER_CIRCLE 360.0;
#define PI 3.141593;

class Robot: public IterativeRobot {
private:
	int replaceThisInt;

	//Declare motors, encoders, and autonomous option
	CANTalon *leftBackMotor;
	CANTalon *leftFrontMotor;
	CANTalon *rightBackMotor;
	CANTalon *rightFrontMotor;

	int autonomousChooser = 0;

	const double wheelDiam = WHEEL_DIAM;
	const double driveDiam = DRIVE_DIAM;
	const double pulsePerRev = PULSE_PER_REV;
	const double degreesPerCircle = DEGREES_PER_CIRCLE;
	const double pi = PI;

	const double pulse_per_inch  = (pulsePerRev) / (wheelDiam * pi);
	const double pulse_per_degree = ((driveDiam * pi) / degreesPerCircle) * pulse_per_inch;

public:

	Robot(){
		leftBackMotor = new CANTalon(9);
		leftFrontMotor = new CANTalon(6);
		rightBackMotor = new CANTalon(7);
		rightFrontMotor = new CANTalon(8);
		leftFrontMotor->SetFeedbackDevice(CANTalon::QuadEncoder);
		rightFrontMotor->SetFeedbackDevice(CANTalon::QuadEncoder);
		leftFrontMotor->ConfigEncoderCodesPerRev(20);
		rightFrontMotor->ConfigEncoderCodesPerRev(20);
	}

	void driveForward(double speed, double distance){
		//wheel = 6 in. diameter
		//20 pulses per revolution
		//20 pulses per 6(pi) or 18.85 inches
		//20 / 18.85 = 0.9425 pulses per 1 inch
		leftFrontMotor->SetPosition(0);
		rightFrontMotor->SetPosition(0);
		double encoderDistance = distance * pulse_per_inch;
		double encoderValue = 0.0;
		while(abs(encoderValue) <= encoderDistance){
			leftFrontMotor->Set(speed);
			leftBackMotor->Set(speed);
			rightFrontMotor->Set(speed);
			rightBackMotor->Set(speed);
			encoderValue = rightFrontMotor->GetPosition();
		}
		leftFrontMotor->Set(0.0);
		leftBackMotor->Set(0.0);
		rightFrontMotor->Set(0.0);
		rightBackMotor->Set(0.0);
		leftFrontMotor->SetPosition(0);
		rightFrontMotor->SetPosition(0);
	}

	void driveBackward(double speed, double distance){
		//wheel = 6 in. diameter
		//20 pulses per revolution
		//20 pulses per 6(pi) or 18.85 inches
		//20 / 18 = 0.9425 pulses per 1 inch
		leftFrontMotor->SetPosition(0);
		rightFrontMotor->SetPosition(0);
		double encoderDistance = distance * pulse_per_inch;
		double encoderValue = 0.0;
		while(abs(encoderValue) <= encoderDistance){
			leftFrontMotor->Set(speed);
			leftBackMotor->Set(speed);
			rightFrontMotor->Set(speed);
			rightBackMotor->Set(speed);
			encoderValue = rightFrontMotor->GetPosition();
		}
		leftFrontMotor->Set(0.0);
		leftBackMotor->Set(0.0);
		rightFrontMotor->Set(0.0);
		rightBackMotor->Set(0.0);
		leftFrontMotor->SetPosition(0);
		rightFrontMotor->SetPosition(0);
	}

	void rotateLeft(double speed, double angle){ //angle in degrees
		//drive diameter =  28.75 in
		//drive circumference = 28.75(pi) = 90.32 in
		//drive arc = 0.25 inches per degree
		//0.9425 pulses per 1 in
		//0.25 * 0.9425 = 0.235625 pulses per degree
		leftFrontMotor->SetPosition(0);
		rightFrontMotor->SetPosition(0);
		double encoderDistance = 0.235625 * angle;
		double encoderValue = 0.0;
		while(abs(encoderValue) <= encoderDistance){
			leftFrontMotor->Set(-speed);
			leftBackMotor->Set(-speed);
			rightFrontMotor->Set(speed);
			rightBackMotor->Set(speed);
			encoderValue = rightFrontMotor->GetPosition();
		}
		leftFrontMotor->Set(0.0);
		leftBackMotor->Set(0.0);
		rightFrontMotor->Set(0.0);
		rightBackMotor->Set(0.0);
		leftFrontMotor->SetPosition(0);
		rightFrontMotor->SetPosition(0);
	}

	void rotateRight(double speed, double angle){ //angle in degrees
		//drive diameter = 28.75 in
		//drive circumference = 28.75(pi) = 90.32 in
		//drive arc = 0.25 inches per degree
		//0.9425 pulses per 1 in
		//0.25 * 0.9425 = 0.235625 pulse per degree
		leftFrontMotor->SetPosition(0);
		rightFrontMotor->SetPosition(0);
		double encoderDistance = 0.235625 * angle;
		double encoderValue = 0.0;
		while(abs(encoderValue) <= encoderDistance){
			leftFrontMotor->Set(speed);
			leftBackMotor->Set(speed);
			rightFrontMotor->Set(-speed);
			rightBackMotor->Set(-speed);
			encoderValue = rightFrontMotor->GetPosition();
		}
		leftFrontMotor->Set(0.0);
		leftBackMotor->Set(0.0);
		rightFrontMotor->Set(0.0);
		rightBackMotor->Set(0.0);
		leftFrontMotor->SetPosition(0);
		rightFrontMotor->SetPosition(0);
	}

	void RobotInit() {

	}

	void AutonomousInit() {
		//Get autonomous choice
		autonomousChooser = replaceThisInt;
		//Autonomous default
		if(autonomousChooser == 0){
			driveForward(0.5, 40.0);
		}
		//Red left
		else if(autonomousChooser == 1){

		}
		//Red center
		else if(autonomousChooser == 2){

		}
		//Red right
		else if(autonomousChooser == 3){

		}
		//Blue left
		else if(autonomousChooser == 4){

		}
		//Blue center
		else if(autonomousChooser == 5){

		}
		//Blue right
		else if(autonomousChooser == 6){

		}
	}


	void AutonomousPeriodic() {

	}

	void TeleopInit() {

	}

	void TeleopPeriodic() {

	}

	void TestPeriodic() {

	}

};

START_ROBOT_CLASS(Robot)
