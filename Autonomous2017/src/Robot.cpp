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
		leftBackMotor = new CANTalon(8);
		leftFrontMotor = new CANTalon(4);
		rightBackMotor = new CANTalon(1);
		rightFrontMotor = new CANTalon(2);
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
		std::cout << "Final: " << encoderDistance << std::endl;
		while(abs(encoderValue) <= encoderDistance){
			leftFrontMotor->Set(speed);
			leftBackMotor->Set(speed);
			rightFrontMotor->Set(speed);
			rightBackMotor->Set(speed);
			encoderValue = rightFrontMotor->GetEncPosition();
			std::cout << "Final: " << encoderDistance << std::endl;
			std::cout << "Current:" << encoderValue <<std::endl;
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
		rightFrontMotor->SetInverted(true);
		rightBackMotor->SetInverted(true);
		//Get autonomous choice
		autonomousChooser = 2;
		//Autonomous default
		if(autonomousChooser == 0){
			driveForward(0.5, 40.0);
		}
		//Red left
		else if(autonomousChooser == 1){
			Timer *red1 = new Timer();
			driveBackward(1.0,53.3);
			rotateRight(0.5,45);
			driveBackward(0.5,52.0);
			red1->Start();
			double time1 = red1 ->Get();
			while(time1<3){
				time1 = red1->Get();
			}
			driveBackward(1.0, 52.0);
			rotateLeft(0.5, 90);
			driveForward(1.0, 120.37);

		}
		//Red center
		else if(autonomousChooser == 2){
			Timer *red2 = new Timer();
			driveForward(1.0 , 90.0);
			red2->Start();
			double time2 = red2->Get();

			while(time2<3){
			time2 = red2->Get();
			}
			//Zack is cheating on you
			driveForward(-0.5,20);
			rotateLeft(1.0,42);
			driveForward(1.0,50.0);

		}
		//Red right
		else if(autonomousChooser == 3){
			Timer *red3 = new Timer();
			driveForward(1.0, 53.3);
			rotateLeft(0.5,45);
			driveForward(0.5,52.0);
			red3->Start();
			double time3 = red3->Get();
			while(time3<3){
				time3 = red3->Get();
			}
			driveBackward(1.0, 52.0);
			rotateRight(0.5, 90);
			driveForward(1.0, 120.37);
		}
		//Blue left
		else if(autonomousChooser == 4){
			Timer *blue1 = new Timer();
			driveForward(1.0,53.3);
			rotateRight(0.5,45);
			driveForward(0.5,52.0);
			blue1->Start();
			double time4 = blue1 ->Get();
			while(time4<3){
				time4 = blue1->Get();
			}
			driveBackward(1.0, 52.0);
			rotateLeft(0.5, 90);
			driveForward(1.0, 120.37);
		}
		//Blue center
		else if(autonomousChooser == 5){
			Timer *blue2 = new Timer();
			driveForward(1.0 , 53.0);
			blue2->Start();
			double time5 = blue2->Get();
			while(time5<3){
				time5 = blue2->Get();
			}
			//Zack is cheating on you
			driveBackward(0.5,5);
			rotateRight(0.5,90);
			driveForward(1.0,20);
			rotateLeft(0.5,90);
			driveForward(1.0,10);
		}
		//Blue right
		else if(autonomousChooser == 6){
			Timer *blue3 = new Timer();
			driveForward(1.0, 53.3);
			rotateLeft(0.5,45);
			driveForward(0.5,52.0);
			blue3->Start();
			double time6 = blue3->Get();
			while(time6<3){
				time6 = blue3->Get();
			}
			driveBackward(1.0, 52.0);
			rotateRight(0.5, 90);
			driveForward(1.0, 120.37);
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
