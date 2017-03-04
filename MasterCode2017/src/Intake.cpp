#include <iostream>
#include <memory>
#include <string>

#include <IterativeRobot.h>
#include <LiveWindow/LiveWindow.h>
#include <Joystick.h>
#include <CANTalon.h>
#include <Intake.h>
#include <SmartDashboard/SendableChooser.h>
#include <SmartDashboard/SmartDashboard.h>

void Intake::IntakeInit(){
	//declare the controller
	controlStick = new Joystick(1);
	//declare intake motor
	intakeMotor = new CANTalon(6);
	intakeForward = false;
	intakeBackward = false;
}

void Intake::RunIntake(){
	//declare buttons
	bool intakeForward = controlStick->GetRawButton(2);
	bool intakeBackward = controlStick->GetRawButton(4);
	//if button 2 is pressed
	if(intakeForward==true){
		//run intake forward
		intakeMotor->Set(-0.6);
	}
	//if button 4 is pressed
	else if(intakeBackward==true){
		//run motor backward
		intakeMotor->Set(0.6);
	}
	//if nothing is pressed
	else{
		intakeMotor->Set(0.0);
	}
}
void Intake::IntakeTeleopPeriodic() {
	//run the intake funtion above
	RunIntake();
}
