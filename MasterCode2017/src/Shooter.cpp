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
	//declares controller / in addition to motors / which will run shooter
	controlStick = new Joystick(1);
	flywheelMotor = new CANTalon(8);
	flywheelMotor->SetFeedbackDevice(CANTalon::QuadEncoder);
	isSpinning = false;
	togglePressed = false;
}

void Shooter::SpinFlywheel(){
	//another toggle / turns the flywheel on and off / it is a button 
	bool toggleSpin = controlStick->GetRawButton(5);
	DriverStation &povStick = DriverStation::GetInstance();
	int pov = povStick.GetStickPOV(1,0);
	if(toggleSpin == true && isSpinning == false && togglePressed == false){
		flywheelSpeed = 1;
		isSpinning = true;
		togglePressed = true;
	}
	else if(toggleSpin == true && isSpinning == true && togglePressed == false){
		flywheelSpeed = 0;
		isSpinning = false;
		togglePressed = true;
	}

	if(toggleSpin == false){
		togglePressed = false;
	}

	//if d-pad up pressed / increase the speed of flywheel / by a count of one 
	if(pov == 0 && upPressed == false){
		if(flywheelSpeed < 4){
			flywheelSpeed++;
		}
		upPressed = true;
	}

	//if up is not pressed / speed of flywheel not increased / boolean is false
	if(pov != 0){
		upPressed = false;
	}

	//if d-pad down pressed / decrease the speed of flywheel / by a count of one 
	if(pov == 180 && downPressed == false){
		if(flywheelSpeed > 1){
			flywheelSpeed--;
		}
		downPressed = true;
	}

	//if up is not pressed / speed of flywheel not increased / boolean is false
	if(pov != 180){
		downPressed = false;
	}

	//spinning the flywheel / using variable speeds / and use dashboard lights
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
	//if flywheel is off / then turn off all of the lights / so drive team can tell
	else{
		flywheelMotor->Set(0.0);
		SmartDashboard::PutBoolean("DB/LED 3", false);
		SmartDashboard::PutBoolean("DB/LED 2", false);
		SmartDashboard::PutBoolean("DB/LED 1", false);
		SmartDashboard::PutBoolean("DB/LED 0", false);
	}
}

void Shooter::ShooterTeleopPeriodic() {
	//spinning the flywheel / using the awesome function / that we wrote ourselves
	SpinFlywheel();
}
