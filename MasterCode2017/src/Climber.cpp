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
	//declares the motor / on the port number seven / for climbing the rope
	ClimberMotor = new CANTalon(7);
	//declares controller / it is also a joystick / on port number one 
	controlStick = new Joystick(1);
}
void Climber::ClimberTeleopPeriodic() {
	//declare the button / the button is button one / it runs the climber 
	bool climb = controlStick->GetRawButton(3);
	//if button is pressed / the motor will start running / at a speed of one 
	if(climb==true){
		ClimberMotor->Set(-1.0);
	}
	//if button not pressed / the motor won't start running / it's at speed zero
	else if(climb==false){
		ClimberMotor->Set(0.0);
	}
}
