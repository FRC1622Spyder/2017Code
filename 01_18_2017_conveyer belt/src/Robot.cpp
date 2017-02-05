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

	CANTalon *motor0 = new CANTalon(0);
	CANTalon *motor1 = new CANTalon(1);
	Joystick *joystick = new Joystick(1);
	bool motoron = false;
	bool buttondown = false;

	void AutonomousInit() override {

	}

	void AutonomousPeriodic() {

	}

	void TeleopInit() {

	}

	void TeleopPeriodic() {
		bool button = joystick->GetRawButton(1);
		if(!buttondown && button==true && motoron==false){
			motoron = true;
			buttondown = true;
		}
		else if(!buttondown && button==true && motoron==true){
			motoron = false;
			buttondown = true;
		}

		if(!button){
			buttondown = false;
		}


		if(motoron==true) {
			motor0->Set(0.5);
			motor1->Set(0.5);
		}
		else if(motoron==false){
			motor0->Set(0.0);
			motor1->Set(0.0);

		}
	}


	void TestPeriodic() {

	}


};

START_ROBOT_CLASS(Robot)
