#include <iostream>
#include <memory>
#include <string>

#include <IterativeRobot.h>
#include <LiveWindow/LiveWindow.h>
#include <Joystick.h>
#include <CANTalon.h>
#include <SmartDashboard/SendableChooser.h>
#include <SmartDashboard/SmartDashboard.h>


class Robot: public frc::IterativeRobot {
public:

	Joystick *joystick0;
	CANTalon *intakemotor; //6
	bool intakeon;
	bool intakeon2;

	Robot(){
		joystick0 = new Joystick(0);
		intakemotor = new CANTalon(6);
		intakeon = false;
		intakeon2 = false;
	}

	/*void intake(){
		bool intakeon = joystick0->GetRawButton(1);
		if(intakeon==true){
			intakemotor->Set(0.2);
		}
		else{
			intakemotor->Set(0.0);
		}
		bool intakeon2 = joystick0->GetRawButton(2);
		if(intakeon2==true){
			intakemotor->Set(-0.2);
		}
		else{
			intakemotor->Set(0.0);
		}

	}*/
	void AutonomousInit() override {

	}

	void AutonomousPeriodic() {

	}

	void TeleopInit() {
		Robot();
	}

	void TeleopPeriodic() {
		intakeon = joystick0->GetRawButton(1);
		intakeon2 = joystick0->GetRawButton(2);
				if(intakeon==true){
					intakemotor->Set(0.4);
					std::cout << "BUTTON 1 ON!" << std::endl;
				}
				else if(intakeon2==true){
					intakemotor->Set(-0.4);
					std::cout << "BUTTON 2 ON!" << std::endl;
				}
				else{
					intakemotor->Set(0.0);
				}
	}

	void TestPeriodic() {

	}


};

START_ROBOT_CLASS(Robot)
