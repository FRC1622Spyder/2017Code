#include <iostream>
#include <memory>
#include <string>

#include <math.h>
#include <IterativeRobot.h>
#include <Joystick.h>
#include <CANTalon.h>
#include <Shooter.h>
#include <LiveWindow/LiveWindow.h>
#include <SmartDashboard/SendableChooser.h>
#include <SmartDashboard/SmartDashboard.h>

void Shooter::ShooterInit(){
	controlStick = new Joystick(1);
	flywheelMotor = new CANTalon(9);

	flywheelMotor->SetFeedbackDevice(CANTalon::QuadEncoder);

	isSpinning = false;
	buttonPressed = false;
}

//Power should be between 1 and 0
void Shooter::SpinFlywheel(double power){
	//Use button to toggle spin
	bool toggleSpin = controlStick->GetRawButton(6);
	std::cout << "toggleSpin: "<< toggleSpin << std::endl;
	std::cout << "isSpinning: " << isSpinning << std::endl;
	std::cout << "buttonPressed: " << buttonPressed << std::endl;
	//If button is pressed, flywheel is not spinning, and button was not pressed before
	//(spin flywheel and set button to 'pressed')
	if(toggleSpin == true && isSpinning == false && buttonPressed == false){
		isSpinning = true;
		buttonPressed = true;
	}
	//If button is pressed, flywheel is spinning, and button was not pressed before
	//(stop spinning flywheel and set button to 'pressed')
	else if(toggleSpin == true && isSpinning == true && buttonPressed == false){
		isSpinning = false;
		buttonPressed = true;
	}

	//If button is not pressed (set button to 'not pressed')
	if(toggleSpin == false){
		buttonPressed = false;
	}

	//Spin flywheel
	if(isSpinning == true){
		//flywheelSpeed = pow(distance, 2) + distance + replaceThisInt;;
		flywheelMotor->Set(power);
	}
	else{
		flywheelMotor->Set(0.0);
	}
}

void Shooter::ShooterTeleopPeriodic() {
	SpinFlywheel(1.0);
}
