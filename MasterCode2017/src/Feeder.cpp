#include <iostream>
#include <memory>
#include <string>

#include <IterativeRobot.h>
#include <Feeder.h>
#include <LiveWindow/LiveWindow.h>
#include <SmartDashboard/SendableChooser.h>
#include <SmartDashboard/SmartDashboard.h>
#include <CANTalon.h>
#include <Joystick.h>

void Feeder::FeederInit(){
	feederMotor = new CANTalon(5);
	controlStick = new Joystick(1);
	isWorking = false;
	buttonPressed = false;
}

void Feeder::FeederTeleopPeriodic() {
	bool toggleWork = controlStick->GetRawButton(2);
	if(buttonPressed==false && toggleWork==true && isWorking==false){
		isWorking = true;
		buttonPressed = true;
	}
	else if(buttonPressed==false && toggleWork==true && isWorking==true){
		isWorking = false;
		buttonPressed = true;
	}

	if(toggleWork==false){
		buttonPressed = false;
	}


	if(isWorking==true) {
		feederMotor->Set(1.0);
	}
	else if(isWorking==false){
		feederMotor->Set(0.0);
	}
}
