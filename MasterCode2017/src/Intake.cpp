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
#include <Config.h>

void Intake::IntakeInit(){
	//declares controller / which runs the intake motor / it is a joystick
	controlStick = new Joystick(1);
	//makes intake motor / it sucks up all of the balls / on port number six
	Config config;
	intakeMotor = new CANTalon(config.GetMotorPort(Config::IntakeMotor));
	IntakeInButton = config.GetControlMapping(Config::IntakeInMapping);
	IntakeOutButton = config.GetControlMapping(Config::IntakeOutMapping);
	intakeForward = false;
	intakeBackward = false;
}

void Intake::RunIntake(){
	//declare more buttons / for intake, forward and back / they're on the joystick
	bool intakeForward = controlStick->GetRawButton(IntakeInButton);
	bool intakeBackward = controlStick->GetRawButton(IntakeOutButton);
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
