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
	//declare the motor
	ClimberMotor = new CANTalon(7);
	//declare the controller
	controlStick = new Joystick(1);
}
void Climber::ClimberTeleopPeriodic() {
	//declare the button 1
	bool climb = controlStick->GetRawButton(1);
	//if button is presses
	if(climb==true){
		//motor is running
		ClimberMotor->Set(-1.0);
	}
	//if button is not pressed
	else if(climb==false){
		//motor is not running
		ClimberMotor->Set(0.0);
	}
}
