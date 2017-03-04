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
	// declare the feeder motor
	feederMotor = new CANTalon(5);
	//declare the controller
	controlStick = new Joystick(1);
}

void Feeder::FeederTeleopPeriodic() {
	//declare the button
	bool toggleWork = controlStick->GetRawButton(8);
	//if button is pressed, run motor
	if(toggleWork == true){
		feederMotor->Set(0.8);
	}
	//if button is not pressed, disable motor
	else if(toggleWork == false){
		feederMotor->Set(0.0);
	}
}
