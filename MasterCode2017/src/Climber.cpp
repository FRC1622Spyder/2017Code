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
	ClimberMotor = new CANTalon(7);//declare the motor
	controlStick = new Joystick(1);//declare the controller
}
void Climber::ClimberTeleopPeriodic() {
	bool climb = controlStick->GetRawButton(1);//declare the button 1
	if(climb==true){//if button is presses
		ClimberMotor->Set(-1.0);//motor is running
	}
	else if(climb==false){//if button is not pressed
		ClimberMotor->Set(0.0);//motor is not running
	}
}
