#include <iostream>
#include <memory>
#include <string>

#include <Flashlight.h>
#include <Relay.h>
#include <Joystick.h>
#include <IterativeRobot.h>

void Flashlight::FlashlightInit(){
	//create a relay / that can light up our flashlight / if button is pressed
	flashlightRelay = new Relay(3);
	//create a joystick / and some boolean values / for our cool flashlight
	drivestick = new Joystick(0);
}

void Flashlight::FlashlightTeleopPeriodic(){
	//this here boolean / makes an on-off for flashlight / based on button five
	bool toggleButton = drivestick->GetRawButton(5);
	//if toggle is on / set the relay to light up / or else turn it off
	if(toggleButton == true){
		flashlightRelay->Set(Relay::Value::kForward);
	}
	else{
		flashlightRelay->Set(Relay::Value::kOff);
	}
}




