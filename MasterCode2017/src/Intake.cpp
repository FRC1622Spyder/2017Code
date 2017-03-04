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
	controlStick = new Joystick(1);//declare the controller
	intakeMotor = new CANTalon(6);//declare intake motor
	intakeForward = false;//declaring a variable false
	intakeBackward = false;//declaring a variable false
}

void Intake::RunIntake(){
	bool intakeForward = controlStick->GetRawButton(2);//declaring button
	bool intakeBackward = controlStick->GetRawButton(4);//declaring button
	if(intakeForward==true){//button 2 is pressed
		intakeMotor->Set(-0.6);//motor is making balls go in
	}
	else if(intakeBackward==true){//button 4 is pressed
		intakeMotor->Set(0.6);//motor is making balls go out
	}
	else{//if nothing is pressed
		intakeMotor->Set(0.0);//not running
	}
}
void Intake::IntakeTeleopPeriodic() {
	RunIntake();//run the intake funtion above
}
