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
	// declare the motor / which will control the feeder / it's a CANTalon
	feederMotor = new CANTalon(5);
	//declare the joystick / which will control the feeder / it is a joystick
	if(SmartDashboard::GetBoolean("DB/Button 0", false) == true){
		controlStick = new Joystick(0);
	} else {
		controlStick = new Joystick(1);
	}
}
void Feeder::FeederTeleopPeriodic() {
	//declare the button / which activates the feeder / is on the joystick 
	bool toggleWork = controlStick->GetRawButton(6);
	//if button is pressed / it will start running motor / at speed of point eight
	if(toggleWork == true){
		feederMotor->Set(0.95);
	}
	//if button not pressed / it will stop running motor / so speed is zero
	else if(toggleWork == false){
		feederMotor->Set(0.0);
	}
}
