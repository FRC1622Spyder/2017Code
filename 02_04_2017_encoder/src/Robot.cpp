#include <iostream>
#include <memory>
#include <string>
#include <math.h>

#include <IterativeRobot.h>
#include <LiveWindow/LiveWindow.h>
#include <SmartDashboard/SendableChooser.h>
#include <SmartDashboard/SmartDashboard.h>
#include <CANTalon.h>
#include <Joystick.h>

class Robot: public frc::IterativeRobot {
private:

	CANTalon *leftFront = new CANTalon(4);
	CANTalon *leftBack = new CANTalon(8);
	CANTalon *rightFront = new CANTalon(2);
	CANTalon *rightBack = new CANTalon(1);
	Joystick *joystick = new Joystick(0);
	bool button = false;
	bool buttonReset = false;
	bool buttononoff = false;
	void RobotInit() {
		rightFront->SetInverted(true);
		rightBack->SetInverted(true);
	}


	void AutonomousInit() {
		leftFront->SetFeedbackDevice(CANTalon::QuadEncoder);
		leftFront->ConfigEncoderCodesPerRev(20);
		//leftFront->SetFeedbackDevice(CANTalon::CtreMagEncoder_Absolute);
		leftFront->SetPosition(0);
		rightFront->SetFeedbackDevice(CANTalon::QuadEncoder);
		rightFront->ConfigEncoderCodesPerRev(20);
		//rightFront->SetFeedbackDevice(CANTalon::CtreMagEncoder_Absolute);
		rightFront->SetPosition(0);
		std::cout<<"Right Begin: "<<rightFront->GetEncPosition()<<std::endl;
		while(abs(rightFront->GetEncPosition()) < 860){
			leftFront->Set(0.5);
			rightFront->Set(0.5);
			rightBack->Set(0.5);
			leftBack->Set(0.5);
		}
		std::cout<<"Right End: "<<rightFront->GetEncPosition()<<std::endl;
		leftFront->Set(0.0);
		leftBack->Set(0.0);
		rightFront->Set(0.0);
		rightBack->Set(0.0);

		leftFront->SetPosition(0);
		rightFront->SetPosition(0);
	}

	void AutonomousPeriodic() {

	}

	void TeleopInit() {
		leftFront->SetFeedbackDevice(CANTalon::QuadEncoder);
		rightFront->SetFeedbackDevice(CANTalon::QuadEncoder);
		leftFront->ConfigEncoderCodesPerRev(20);
		//leftFront->SetFeedbackDevice(CANTalon::CtreMagEncoder_Absolute);
		rightFront->ConfigEncoderCodesPerRev(20);
		//rightFront->SetFeedbackDevice(CANTalon::CtreMagEncoder_Absolute);
	}

	void TeleopPeriodic() {
		button = joystick->GetRawButton(1);
		buttonReset = joystick->GetRawButton(2);
		if(buttonReset == true){
			leftFront->SetPosition(0);
			rightFront->SetPosition(0);
		}
		if(button == true){
		std::cout<<"Left: "<<leftFront->GetEncPosition()<<std::endl;
		std::cout<<"Right: "<<rightFront->GetEncPosition()<<std::endl;
		}
		buttononoff = joystick->GetRawButton(3);
		if(buttononoff == true){
			leftFront->Set(0.5);
			rightFront->Set(-0.5);
			rightBack->Set(-0.5);
			leftBack->Set(0.5);
		}
		else if(buttononoff == false){
			leftFront->Set(0.0);
			leftBack->Set(0.0);
			rightFront->Set(0.0);
			rightBack->Set(0.0);
		}
	}

	void TestPeriodic() {

	}


};

START_ROBOT_CLASS(Robot)
