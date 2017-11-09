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
	//declares controller / which runs the intake motor / it is a joystick
	if(SmartDashboard::GetBoolean("DB/Button 0", false) == true){
		controlStick = new Joystick(0);
	} else {
		controlStick = new Joystick(1);
	}
	//makes intake motor / it sucks up all of the balls / on port number six
	intakeMotor = new CANTalon(6);
	intakeForward = false;
	intakeBackward = false;
}

void Intake::RunIntake(){
	//declare more buttons / for intake, forward and back / they're on the joystick
	bool intakeForward = controlStick->GetRawButton(1);
	bool intakeBackward = controlStick->GetRawButton(4);
	//if button two pressed / it will run intake forward / at speed of point six
	if(intakeForward==true){
		intakeMotor->Set(-0.6);
	}
	//if button four pressed / intake will be run backward / also at point six
	else if(intakeBackward==true){
		intakeMotor->Set(0.6);
	}
	//if no button pressed / makes the intake stop moving / so speed is zero
	else{
		intakeMotor->Set(0.0);
	}
}
void Intake::IntakeTeleopPeriodic() {
	//this is a function / it runs the code above / and hopefully works
	RunIntake();
}
