#include <iostream>
#include <memory>
#include <string>

#include <IterativeRobot.h>
#include <LiveWindow/LiveWindow.h>
#include <SmartDashboard/SendableChooser.h>
#include <SmartDashboard/SmartDashboard.h>
#include <CANTalon.h>
#include <Climber.h>
#include <Joystick.h>

void Climber::ClimberInit(){
	ClimberMotor = new CANTalon(7);
	controlStick = new Joystick(1);
	isWorking = false;
	buttonPressed = false;
	climbDirection = true;
}

	void Climber::ClimberTeleopPeriodic() {
		bool climbup = controlStick->GetRawButton(5);
		bool climbdown = controlStick->GetRawButton(7);
		if(buttonPressed==false && climbup==true && isWorking==false){
			isWorking = true;
			buttonPressed = true;
			climbDirection = true;
		}
		else if(buttonPressed==false && climbup==true && isWorking==true){
			isWorking = false;
			buttonPressed = true;
			climbDirection = true;
		}
		else if(buttonPressed==false && climbdown==true && isWorking==false){
			isWorking = true;
			buttonPressed = true;
			climbDirection = false;
		}
		else if(buttonPressed==false && climbdown==true && isWorking==true){
			isWorking = false;
			buttonPressed = true;
			climbDirection = false;
		}

		if(climbup==false){
			buttonPressed = false;
		}


		if(isWorking==true && climbDirection==true) {
			ClimberMotor->Set(1.0);
		}
		else if(isWorking==true && climbDirection==false){
			ClimberMotor->Set(-0.5);
		}
		else if(isWorking==false){
			ClimberMotor->Set(0.0);
		}

	}

