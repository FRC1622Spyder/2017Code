#include <iostream>
#include <memory>
#include <string>

#include <math.h>
#include <IterativeRobot.h>
#include <Joystick.h>
#include <CANTalon.h>
#include <LiveWindow/LiveWindow.h>
#include <SmartDashboard/SendableChooser.h>
#include <SmartDashboard/SmartDashboard.h>

class Robot:public IterativeRobot {

private:

	//Declare booleans
	bool isSpinning = false;
	bool buttonPressed = false;

	//Declare joystick and motors
	Joystick *controlStick = new Joystick(0);
	CANTalon *flywheelMotor = new CANTalon(9); //9

public:

	Robot(){
		//controlStick = new Joystick(0);
		//flywheelMotor = new CANTalon(6);
	}

	//Power should be between 1 and 0
	void spinFlywheel(double power){
		//Use button to toggle spin
		bool toggleSpin = controlStick->GetRawButton(1);
		std::cout << "toggleSpin: "<< toggleSpin << std::endl;
		std::cout << "isSpinning: " << isSpinning << std::endl;
		std::cout << "buttonPressed: " << buttonPressed << std::endl;
		//If button is pressed, flywheel is not spinning, and button was not pressed before
		//(spin flywheel and set button to 'pressed')
		if(toggleSpin == true && isSpinning == false && buttonPressed == false){
			isSpinning = true;
			buttonPressed = true;
		}
		//If button is pressed, flywheel is spinning, and button was not pressed before
		//(stop spinning flywheel and set button to 'pressed')
		else if(toggleSpin == true && isSpinning == true && buttonPressed == false){
			isSpinning = false;
			buttonPressed = true;
		}

		//If button is not pressed (set button to 'not pressed')
		if(toggleSpin == false){
			buttonPressed = false;
		}

		//Spin flywheel
		if(isSpinning == true){
			//flywheelSpeed = pow(distance, 2) + distance + replaceThisInt;;
			flywheelMotor->Set(power);
		}
		else{
			flywheelMotor->Set(0.0);
		}
	}

	void RobotInit() {
	}

	void AutonomousInit() {
	}

	void AutonomousPeriodic() {
	}

	void TeleopInit() {
	}

	void TeleopPeriodic() {
		spinFlywheel(1.0);
	}

	void TestPeriodic() {
	}
};

START_ROBOT_CLASS(Robot)
