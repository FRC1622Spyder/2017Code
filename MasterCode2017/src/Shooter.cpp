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
	controlStick = new Joystick(1);
	flywheelMotor = new CANTalon(8);//6 on test robot, 8 on real

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

	if(pov == 0 && upPressed == false){//if up on
		if(flywheelSpeed < 4){
			flywheelSpeed++;
		}
		upPressed = true;
	}

	if(pov != 0){//if not equal to 0
		upPressed = false;//speed increse not presses
	}

	if(pov == 180 && downPressed == false){
		if(flywheelSpeed > 1){
			flywheelSpeed--;
		}
		downPressed = true;
	}

	if(pov != 180){
		downPressed = false;
	}

	//Spin flywheel
	if(isSpinning == true){
		if(flywheelSpeed == 1){
			flywheelMotor->Set(-0.7);
			SmartDashboard::PutBoolean("DB/LED 3", true);
			SmartDashboard::PutBoolean("DB/LED 2", false);
			SmartDashboard::PutBoolean("DB/LED 1", false);
			SmartDashboard::PutBoolean("DB/LED 0", false);
		}
		else if(flywheelSpeed == 2){
			flywheelMotor->Set(-0.8);
			SmartDashboard::PutBoolean("DB/LED 3", true);
			SmartDashboard::PutBoolean("DB/LED 2", true);
			SmartDashboard::PutBoolean("DB/LED 1", false);
			SmartDashboard::PutBoolean("DB/LED 0", false);
		}
		else if(flywheelSpeed == 3){
			flywheelMotor->Set(-0.9);
			SmartDashboard::PutBoolean("DB/LED 3", true);
			SmartDashboard::PutBoolean("DB/LED 2", true);
			SmartDashboard::PutBoolean("DB/LED 1", true);
			SmartDashboard::PutBoolean("DB/LED 0", false);
		}
		else if(flywheelSpeed == 4){
			flywheelMotor->Set(-1.0);
			SmartDashboard::PutBoolean("DB/LED 3", true);
			SmartDashboard::PutBoolean("DB/LED 2", true);
			SmartDashboard::PutBoolean("DB/LED 1", true);
			SmartDashboard::PutBoolean("DB/LED 0", true);
		}
		else {
			SmartDashboard::PutBoolean("DB/LED 3", false);
			SmartDashboard::PutBoolean("DB/LED 2", false);
			SmartDashboard::PutBoolean("DB/LED 1", false);
			SmartDashboard::PutBoolean("DB/LED 0", false);
		}
	}
	else{
		flywheelMotor->Set(0.0);
		SmartDashboard::PutBoolean("DB/LED 3", false);
		SmartDashboard::PutBoolean("DB/LED 2", false);
		SmartDashboard::PutBoolean("DB/LED 1", false);
		SmartDashboard::PutBoolean("DB/LED 0", false);
	}
}

void Shooter::ShooterTeleopPeriodic() {
	SpinFlywheel();
}
