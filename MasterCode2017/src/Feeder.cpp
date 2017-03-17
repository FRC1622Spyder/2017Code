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
#include <Config.h>

void Feeder::FeederInit(){
	// declare the motor / which will control the feeder / it's a CANTalon
	Config config;
	feederMotor = new CANTalon(config.GetMotorPort(Config::FeederMotor));
	FeederButton = config.GetControlMapping(Config::FeederMapping);
	//declare the joystick / which will control the feeder / it is a joystick
	controlStick = new Joystick(1);
}

void Feeder::FeederTeleopPeriodic() {
	//declare the button / which activates the feeder / is on the joystick 
	bool toggleWork = controlStick->GetRawButton(FeederButton);
	//if button is pressed / it will start running motor / at speed of point eight
	if(toggleWork == true){
		feederMotor->Set(-0.95);
	}
	//if button not pressed / it will stop running motor / so speed is zero
	else if(toggleWork == false){
		feederMotor->Set(0.0);
	}
}
