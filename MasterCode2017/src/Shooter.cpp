#include <iostream>
#include <memory>
#include <string>

#include <math.h>
#include <IterativeRobot.h>
#include <Shooter.h>
#include <DriverStation.h>
#include <Joystick.h>
#include <CANTalon.h>
#include <LiveWindow/LiveWindow.h>
#include <SmartDashboard/SendableChooser.h>
#include <SmartDashboard/SmartDashboard.h>

void Shooter::ShooterInit(){
	//declare controller and motors
	controlStick = new Joystick(1);
	flywheelMotor = new CANTalon(8);
	//add an encoder
	flywheelMotor->SetFeedbackDevice(CANTalon::QuadEncoder);
	isSpinning = false;
	togglePressed = false;
}
//Power should be between 1 and 0
void Shooter::SpinFlywheel(){
	//Use button to toggle spin
	bool toggleSpin = controlStick->GetRawButton(6);
	DriverStation &povStick = DriverStation::GetInstance();
	int pov = povStick.GetStickPOV(1,0);
	//If button is pressed, flywheel is not spinning, and button was not pressed before
	//(spin flywheel and set button to 'pressed')
	if(toggleSpin == true && isSpinning == false && togglePressed == false){
		flywheelSpeed = 1;
		isSpinning = true;
		togglePressed = true;
	}
	//If button is pressed, flywheel is spinning, and button was not pressed before
	//(stop spinning flywheel and set button to 'pressed')
	else if(toggleSpin == true && isSpinning == true && togglePressed == false){
		flywheelSpeed = 0;
		isSpinning = false;
		togglePressed = true;
	}

	//If button is not pressed (set button to 'not pressed')
	if(toggleSpin == false){
		togglePressed = false;
	}

	//if up on the d-pad is pressed
	if(pov == 0 && upPressed == false){
		if(flywheelSpeed < 4){
			//decrease the motor speed by 1 factor
			flywheelSpeed++;
		}
		//set variable to false
		upPressed = true;
	}

	//if up on the d-pad is not pressed
	if(pov != 0){
		//speed increase not pressed
		upPressed = false;
	}

	//if down on the d-pad is pressed
	if(pov == 180 && downPressed == false){
		if(flywheelSpeed > 1){
			//decrease the motor speed by 1 factor
			flywheelSpeed--;
		}
		//set variable to false
		downPressed = true;
	}

	//if down on the d-pad is not pressed
	if(pov != 180){
		//speed decrease not pressed
		downPressed = false;
	}

	//Spin flywheel
	if(isSpinning == true){
		//if flywheel is at lowest speed, activate 1 light and set speed to 0.7
		if(flywheelSpeed == 1){
			flywheelMotor->Set(-0.7);
			SmartDashboard::PutBoolean("DB/LED 3", true);
			SmartDashboard::PutBoolean("DB/LED 2", false);
			SmartDashboard::PutBoolean("DB/LED 1", false);
			SmartDashboard::PutBoolean("DB/LED 0", false);
		}
		//if flywheel is at second speed, activate 2 lights and set speed to 0.8
		else if(flywheelSpeed == 2){
			flywheelMotor->Set(-0.8);
			SmartDashboard::PutBoolean("DB/LED 3", true);
			SmartDashboard::PutBoolean("DB/LED 2", true);
			SmartDashboard::PutBoolean("DB/LED 1", false);
			SmartDashboard::PutBoolean("DB/LED 0", false);
		}
		//if flywheel is at third speed, activate 3 lights and set speed to 0.9
		else if(flywheelSpeed == 3){
			flywheelMotor->Set(-0.9);
			SmartDashboard::PutBoolean("DB/LED 3", true);
			SmartDashboard::PutBoolean("DB/LED 2", true);
			SmartDashboard::PutBoolean("DB/LED 1", true);
			SmartDashboard::PutBoolean("DB/LED 0", false);
		}
		//if flywheel is at highest speed, activate 4 lights and set speed to 1.0
		else if(flywheelSpeed == 4){
			flywheelMotor->Set(-1.0);
			SmartDashboard::PutBoolean("DB/LED 3", true);
			SmartDashboard::PutBoolean("DB/LED 2", true);
			SmartDashboard::PutBoolean("DB/LED 1", true);
			SmartDashboard::PutBoolean("DB/LED 0", true);
		}
		//if flywheel is off, turn all lights off
		else {
			SmartDashboard::PutBoolean("DB/LED 3", false);
			SmartDashboard::PutBoolean("DB/LED 2", false);
			SmartDashboard::PutBoolean("DB/LED 1", false);
			SmartDashboard::PutBoolean("DB/LED 0", false);
		}
	}
	//if flywheel is off, turn all lights off
	else{
		flywheelMotor->Set(0.0);
		SmartDashboard::PutBoolean("DB/LED 3", false);
		SmartDashboard::PutBoolean("DB/LED 2", false);
		SmartDashboard::PutBoolean("DB/LED 1", false);
		SmartDashboard::PutBoolean("DB/LED 0", false);
	}
}

void Shooter::ShooterTeleopPeriodic() {
	//spin the flywheel
	SpinFlywheel();
}
