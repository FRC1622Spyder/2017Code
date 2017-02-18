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
	controlStick = new Joystick(1);
	intakeMotor = new CANTalon(6);
	intakeForward = false;
	intakeBackward = false;
}

void Intake::RunIntake(){
	bool intakeForward = controlStick->GetRawButton(6);
	bool intakeBackward = controlStick->GetRawButton(8);
	if(intakeForward==true){
		intakeMotor->Set(-0.6);
	}
	else if(intakeBackward==true){
		intakeMotor->Set(0.6);
	}
	else{
		intakeMotor->Set(0.0);
	}

}

void Intake::IntakeTeleopPeriodic() {
	RunIntake();
}
