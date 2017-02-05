#include <iostream>
#include <memory>
#include <string>

#include <IterativeRobot.h>
#include <LiveWindow/LiveWindow.h>
#include <SmartDashboard/SendableChooser.h>
#include <SmartDashboard/SmartDashboard.h>
#include <CANTalon.h>
#include <Joystick.h>

class Robot: public frc::IterativeRobot {
private:

	CANTalon *TANcalon = new CANTalon(2);
	CANTalon *back = new CANTalon(1);
	Joystick *joystick = new Joystick(0);
	bool button = false;
	bool buttonReset = false;

	void RobotInit() {

	}


	void AutonomousInit() override {

	}

	void AutonomousPeriodic() {

	}

	void TeleopInit() {
		TANcalon->SetFeedbackDevice(CANTalon::QuadEncoder);
	}

	void TeleopPeriodic() {
		TANcalon->Set(0.1);
		back->Set(0.1);
		button = joystick->GetRawButton(1);
		buttonReset = joystick->GetRawButton(2);
		if(buttonReset == true){
			TANcalon->SetPosition(0);
		}
		if(button == true){
		std::cout<<TANcalon->GetEncPosition()<<std::endl;
		}

	}

	void TestPeriodic() {

	}


};

START_ROBOT_CLASS(Robot)
