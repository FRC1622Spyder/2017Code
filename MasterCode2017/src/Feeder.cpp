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
	feederMotor = new CANTalon(5);// declare the feeder motor
	controlStick = new Joystick(1);//declare the controller
}

void Feeder::FeederTeleopPeriodic() {
	bool toggleWork = controlStick->GetRawButton(8);//declare the button
	if(toggleWork == true){//button is pressed
		feederMotor->Set(0.8);//motor going at 80% full speed
	}
	else if(toggleWork == false){//button not pressed
		feederMotor->Set(0.0);//motor off
	}
}
