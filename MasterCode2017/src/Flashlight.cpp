#include <iostream>
#include <memory>
#include <string>

#include <Flashlight.h>
#include <Relay.h>
#include <Joystick.h>
#include <IterativeRobot.h>

void Flashlight::FlashlightInit(){
	flashlightRelay = new Relay(3);
	drivestick = new Joystick(0);
	isLit = false;
	toggleOn = false;
}

void Flashlight::FlashlightTeleopPeriodic(){
	bool toggleButton = drivestick->GetRawButton(5);
	if(isLit == false && toggleButton == true && toggleOn == false) {
		isLit = true;
		toggleOn = true;
	}
	else if(isLit == true && toggleButton == true && toggleOn == false){
		isLit =  false;
		toggleOn = true;
	}
	if(toggleButton == false){
		toggleOn = false;
	}
	if(isLit == true){
		flashlightRelay->Set(Relay::Value::kForward);
	}
	else{
		flashlightRelay->Set(Relay::Value::kOff);
	}
}




