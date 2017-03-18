/*
 * Autonomous.cpp
 *
 *  Created on: Feb 20, 2017
 *      Author: Zack
 */
#include <iostream>
#include <memory>
#include <string>

#include <IterativeRobot.h>
#include <Joystick.h>
#include <CANTalon.h>
#include <Autonomous.h>
#include <Dashboard.h>
#include <Config.h>
#include <LiveWindow/LiveWindow.h>
#include <SmartDashboard/SendableChooser.h>
#include <SmartDashboard/SmartDashboard.h>

void Autonomous::DriveForward(double speed, double distance){
	//Periodic mode / updates each twenty ms/ time and time again
	double encoderValue = leftFrontMotor->GetEncPosition();
	double encoderDistance = distance * pulse_per_inch;
	//the robot moves while / the encoder is less than / the total distance
	if(abs(encoderValue) <= encoderDistance){
		leftFrontMotor->Set(speed);
		leftBackMotor->Set(speed);
		rightFrontMotor->Set(speed);
		rightBackMotor->Set(speed);
	}
	//pause for twenty five / periods which means the time / zero point five seconds
	else if(counter <= 25){
		leftFrontMotor->Set(0.0);
		leftBackMotor->Set(0.0);
		rightFrontMotor->Set(0.0);
		rightBackMotor->Set(0.0);
		counter++;
	}
	//clean slate we need to / reset the values of auto / add one to auto phase
	else {
		leftFrontMotor->Set(0.0);
		leftBackMotor->Set(0.0);
		rightFrontMotor->Set(0.0);
		rightBackMotor->Set(0.0);
		leftFrontMotor->SetEncPosition(0);
		rightFrontMotor->SetEncPosition(0);
		counter = 0;
		autonomousPhase++;
	}
}

void Autonomous::DriveBackward(double speed, double distance){
	//Periodic mode / updates each twenty ms/ time and time again
	double encoderValue = leftFrontMotor->GetEncPosition();
	double encoderDistance = distance * pulse_per_inch;
	//the robot moves while / the encoder is less than / the total distance
	if(abs(encoderValue) <= encoderDistance){
		leftFrontMotor->Set(-speed);
		leftBackMotor->Set(-speed);
		rightFrontMotor->Set(-speed);
		rightBackMotor->Set(-speed);
	}
	//pause for twenty five / periods which means the time / zero point five seconds
	else if(counter <= 25){
		leftFrontMotor->Set(0.0);
		leftBackMotor->Set(0.0);
		rightFrontMotor->Set(0.0);
		rightBackMotor->Set(0.0);
		counter++;
		std::cout << counter << std::endl;
	}
	//clean slate we need to / reset the values of auto / add one to auto phase
	else {
		leftFrontMotor->Set(0.0);
		leftBackMotor->Set(0.0);
		rightFrontMotor->Set(0.0);
		rightBackMotor->Set(0.0);
		leftFrontMotor->SetEncPosition(0);
		rightFrontMotor->SetEncPosition(0);
		counter = 0;
		autonomousPhase++;
	}
}

void Autonomous::RotateCounterclockwise(double speed, double angle){
	//Periodic mode / updates each twenty ms/ time and time again
	double encoderValue = leftFrontMotor->GetEncPosition();
	double radianAngle = angle * (pi /180);
	double encoderDistance =  radianAngle * pulse_per_radian;
	//the robot moves while / the encoder is less than / the total distance
	if(abs(encoderValue) <= encoderDistance){
		leftFrontMotor->Set(-speed);
		leftBackMotor->Set(-speed);
		rightFrontMotor->Set(speed);
		rightBackMotor->Set(speed);
	}
	//pause for twenty five / periods which means the time / zero point five seconds
	else if(counter <= 25){
		leftFrontMotor->Set(0.0);
		leftBackMotor->Set(0.0);
		rightFrontMotor->Set(0.0);
		rightBackMotor->Set(0.0);
		counter++;
	}
	//clean slate we need to / reset the values of auto / add one to auto phase
	else {
		leftFrontMotor->Set(0.0);
		leftBackMotor->Set(0.0);
		rightFrontMotor->Set(0.0);
		rightBackMotor->Set(0.0);
		leftFrontMotor->SetEncPosition(0);
		rightFrontMotor->SetEncPosition(0);
		counter = 0;
		autonomousPhase++;
	}
}

void Autonomous::RotateClockwise(double speed, double angle){
	//Periodic mode / updates each twenty ms/ time and time again
	double encoderValue = leftFrontMotor->GetEncPosition();
	double radianAngle = angle * (pi /180);
	double encoderDistance =  radianAngle * pulse_per_radian;
	//the robot moves while / the encoder is less than / the total distance
	if(abs(encoderValue) <= encoderDistance){
		leftFrontMotor->Set(speed);
		leftBackMotor->Set(speed);
		rightFrontMotor->Set(-speed);
		rightBackMotor->Set(-speed);
	//pause for twenty five / periods which means the time / zero point five seconds
	}
	else if(counter <= 25){
		leftFrontMotor->Set(0.0);
		leftBackMotor->Set(0.0);
		rightFrontMotor->Set(0.0);
		rightBackMotor->Set(0.0);
		counter++;
	}
	//clean slate we need to / reset the values of auto / add one to auto phase
	else {
		leftFrontMotor->Set(0.0);
		leftBackMotor->Set(0.0);
		rightFrontMotor->Set(0.0);
		rightBackMotor->Set(0.0);
		leftFrontMotor->SetEncPosition(0);
		rightFrontMotor->SetEncPosition(0);
		counter = 0;
		autonomousPhase++;
	}
}

void Autonomous::Shoot(double speed, double time){
	double periods = time * 50;
	if(counter <= periods){
		shooterMotor->Set(-speed);
		if(counter >= 50){
			feederMotor->Set(-0.95);
		}
		counter++;
	}
	else{
		feederMotor->Set(0.0);
		shooterMotor->Set(0.0);
		counter = 0;
		autonomousPhase++;
	}
}

void Autonomous::Wait(double time){
	double periods = time * 50;
	if(counter <= periods){
		leftFrontMotor->Set(0.0);
		leftBackMotor->Set(0.0);
		rightFrontMotor->Set(0.0);
		rightBackMotor->Set(0.0);
		counter++;
	}
	else{
		counter = 0;
		autonomousPhase++;
	}
}

void Autonomous::AutonomousInit(){
	//declaring the motors / ports 1 through 4 oh what fun / they are CANTalons
	Config config;
	leftBackMotor = new CANTalon(config.GetMotorPort(Config::LeftBackMotor));
	leftFrontMotor = new CANTalon(config.GetMotorPort(Config::LeftFrontMotor));
	rightBackMotor = new CANTalon(config.GetMotorPort(Config::RightBackMotor));
	rightFrontMotor = new CANTalon(config.GetMotorPort(Config::RightFrontMotor));

	shooterMotor = new CANTalon(config.GetMotorPort(Config::ShooterMotor));
	feederMotor = new CANTalon(config.GetMotorPort(Config::FeederMotor));

	rightBackMotor->SetInverted(true);
	rightFrontMotor->SetInverted(true);

	leftFrontMotor->SetFeedbackDevice(CANTalon::QuadEncoder);
	rightFrontMotor->SetFeedbackDevice(CANTalon::QuadEncoder);

	leftFrontMotor->ConfigEncoderCodesPerRev(20);
	rightFrontMotor->ConfigEncoderCodesPerRev(20);

	leftFrontMotor->SetEncPosition(0);
	rightFrontMotor->SetEncPosition(0);

	Dashboard dashboard;
	autonomousPhase = 0;
	counter = 0;
	autonomousChooser = dashboard.AutoSelect();
}

void Autonomous::AutonomousPeriodic(){
	//encoders might break / that would be bad if we didn't / have a back up plan
	if(autonomousChooser == 0){

	}
	//our spot is red left / triggers one hopper after / we go for the gear
	//except that we don't / hit a hopper anymore / because it's too hard
	else if(autonomousChooser == 1){
		if (autonomousPhase == 0){
			DriveBackward(0.5,57.0);//gear port is on back / so we must drive backwards to / deliver the gear
		}
		else if (autonomousPhase == 1){
			RotateClockwise(0.3,65.0);//rotate clockwise to / drive to the airship to dock / pray we hit the spike
		}
		else if (autonomousPhase == 2){
			DriveBackward(0.4,60.0);
		}
		else if (autonomousPhase == 3){
			Wait(3.0);//wait for the human / why are they so very slow / let us hurry up
		}
	}
	//our spot is red mid / triggers one hopper after / we go for the gear
	//except that we don't / hit a hopper anymore / because it's too hard
	else if(autonomousChooser == 2){
		if(autonomousPhase == 0){
			DriveBackward(0.5,59.0);//gear port is on back / so we must drive backwards to / deliver the gear
		}
		else if(autonomousPhase == 1){
			Wait(3.0);//wait for the human / why are they so very slow / let us hurry up
		}
	}
	//our spot is red right / triggers one hopper after / we go for the gear
	//except that we don't / hit a hopper anymore / because it's too hard
	else if (autonomousChooser == 3){
		if (autonomousPhase == 0){
			DriveBackward(0.5,57.0);//gear port is on back / so we must drive backwards to / deliver the gear
		}
		else if (autonomousPhase == 1){
			RotateCounterclockwise(0.3,65.0);//rotate clockwise to / drive to the airship to dock / pray we hit the spike
		}
		else if (autonomousPhase == 2){
			DriveBackward(0.4,60.0);
		}
		else if (autonomousPhase == 3){
			Wait(3.0);//wait for the human / why are they so very slow / let us hurry up
		}
	}
	//our spot is blue left / triggers one hopper after / we go for the gear
	//except that we don't / hit a hopper anymore / because it's too hard
	else if (autonomousChooser == 4){
		if (autonomousPhase == 0){
			DriveBackward(0.5,57.0);//gear port is on back / so we must drive backwards to / deliver the gear
		}
		else if (autonomousPhase == 1){
			RotateClockwise(0.3,65.0);//rotate clockwise to / drive to the airship to dock / pray we hit the spike
		}
		else if (autonomousPhase == 2){
			DriveBackward(0.4,60.0);
		}
		else if (autonomousPhase == 3){
			Wait(3.0);//wait for the human / why are they so very slow / let us hurry up
		}
	}
	//our spot is blue mid / triggers one hopper after / we go for the gear
	//except that we don't / hit a hopper anymore / because it's too hard
	else if (autonomousChooser == 5){
		if(autonomousPhase == 0){
			DriveBackward(0.5, 59.0);//gear port is on back / so we must drive backwards to / deliver the gear
		}
		else if(autonomousPhase == 1){
			Wait(3.0);//wait for the human / why are they so very slow / let us hurry up
		}
	}
	//our spot is blue right / triggers one hopper after / we go for the gear
	//except that we don't / hit a hopper anymore / because it's too hard
	else if (autonomousChooser == 6){
		if (autonomousPhase == 0){
			DriveBackward(0.5,57.0);//gear port is on back / so we must drive backwards to / deliver the gear
		}
		else if (autonomousPhase == 1){
			RotateCounterclockwise(0.3,65.0);//rotate clockwise to / drive to the airship to dock / pray we hit the spike
		}
		else if (autonomousPhase == 2){
			DriveBackward(0.4,60.0);
		}
		else if (autonomousPhase == 3){
			Wait(3.0);//wait for the human / why are they so very slow / let us hurry up
		}
	}
	//our spot is red left / triggers one hopper only / we don't do a gear
	if(autonomousChooser == 7){
		if(autonomousPhase == 0){
			DriveBackward(0.7,208.9);//drive back to hopper / rotate to face the hopper / get all of the balls
		}
		else if (autonomousPhase == 1){
			RotateClockwise(0.3,90);
		}
		else if (autonomousPhase == 2){
			DriveForward(0.7,91.6);
		}
	}
	//our spot is red mid / triggers two hoppers only / we don't do a gear
	else if(autonomousChooser == 8){

		if(autonomousPhase == 0){
			DriveBackward(0.7,46.7);//drive backward and turn / we do that three times total / drive forward and turn
		}
		else if (autonomousPhase == 1){
			RotateCounterclockwise(0.3,90.0);
		}
		else if (autonomousPhase == 2){
			DriveForward(0.7,70.3);
		}
		else if (autonomousPhase == 3){
			RotateCounterclockwise(0.3,90.0);
		}
		else if (autonomousPhase == 4){
			DriveForward(0.7,34.3);
		}
		else if (autonomousPhase == 5){
			RotateClockwise(0.3,90.0);
		}
		else if (autonomousPhase == 6){
			DriveForward(0.7,91.6);//rotate to hopper / we hit it head on for balls / to fall on the bot
		}
		else if (autonomousPhase == 7){
			Wait(3.0);//wait for falling balls / they take some time to fall out / because gravity
		}
		else if (autonomousPhase == 8){
			DriveBackward(0.7,91.6);
		}
		else if (autonomousPhase == 9){
			RotateClockwise(0.3,90.0);//face the front again / drive forward to next hopper / we hit two get r3kt
		}
		else if (autonomousPhase == 10){
			DriveForward(0.7, 240.3);
		}
		else if (autonomousPhase == 11){
			RotateCounterclockwise(0.3,90.0);//rotate to hopper / we hit it head on for balls / to fall on the bot
		}
		else if (autonomousPhase == 12){
			DriveForward(0.7,91.6);
		}
	}

	//our spot is red right / triggers two hoppers only / we don't do a gear
	else if(autonomousChooser == 9){
		if(autonomousPhase == 0){
			DriveBackward(0.7,81.0);//drive to face hopper / we hit it head on for balls / to fall on the bot
		}
		else if (autonomousPhase == 1){
			RotateCounterclockwise(0.3,90.0);
		}
		else if (autonomousPhase == 2){
			DriveForward(0.7,91.6);
		}
		else if (autonomousPhase == 3){
			Wait(3.0);//wait for falling balls / they take some time to fall out / because gravity
		}
		else if (autonomousPhase == 4){
			DriveBackward(0.7,91.6);//face the front again / drive forward to next hopper / we hit two get r3kt
		}
		else if (autonomousPhase == 5){
			RotateCounterclockwise(0.3,90.0);
		}
		else if (autonomousPhase == 6){
			DriveForward(0.7, 240.3);
		}
		else if (autonomousPhase == 7){
			RotateClockwise(0.3,90.0);//rotate to hopper / we hit it head on for balls / to fall on the bot
		}
		else if (autonomousPhase == 8){
			DriveForward(0.7,91.6);
		}
	}
	//our spot is blue left / triggers two hoppers only / we don't do a gear
	else if(autonomousChooser == 10){
		if(autonomousPhase == 0){
			DriveBackward(0.7,81.0);//drive to face hopper / we hit it head on for balls / to fall on the bot
		}
		else if (autonomousPhase == 1){
			RotateClockwise(0.3,90.0);
		}
		else if (autonomousPhase == 2){
			DriveForward(0.7,91.6);
		}
		else if (autonomousPhase == 3){
			Wait(3.0);//wait for falling balls / they take some time to fall out / because gravity
		}
		else if (autonomousPhase == 4){
			DriveBackward(0.7,91.6);//face the front again / drive forward to next hopper / we hit two get r3kt
		}
		else if (autonomousPhase == 5){
			RotateClockwise(0.3,90.0);
		}
		else if (autonomousPhase == 6){
			DriveForward(0.7, 240.3);
		}
		else if (autonomousPhase == 7){
			RotateCounterclockwise(0.3,90.0);//rotate to hopper / we hit it head on for balls / to fall on the bot
		}
		else if (autonomousPhase == 8){
			DriveForward(0.7,91.6);
		}
	}
	//our spot is blue mid / triggers two hoppers only / we don't do a gear
	else if(autonomousChooser == 11){
		if(autonomousPhase == 0){
			DriveBackward(0.7,46.7);//drive backward and turn / we do that three times total / drive forward and turn
		}
		else if (autonomousPhase == 1){
			RotateClockwise(0.3,90.0);
		}
		else if (autonomousPhase == 2){
			DriveForward(0.7,70.3);
		}
		else if (autonomousPhase == 3){
			RotateClockwise(0.3,90.0);
		}
		else if (autonomousPhase == 4){
			DriveForward(0.7,34.3);
		}
		else if (autonomousPhase == 5){
			RotateCounterclockwise(0.3,90.0);
		}
		else if (autonomousPhase == 6){
			DriveForward(0.7,91.6);//rotate to hopper / we hit it head on for balls / to fall on the bot
		}
		else if (autonomousPhase == 7){
			Wait(3.0);//wait for falling balls / they take some time to fall out / because gravity
		}
		else if (autonomousPhase == 8){
			DriveBackward(0.7,91.6);//face the front again / drive forward to next hopper / we hit two get r3kt
		}
		else if (autonomousPhase == 9){
			RotateClockwise(0.3,90.0);
		}
		else if (autonomousPhase == 10){
			DriveForward(0.7, 240.3);
		}
		else if (autonomousPhase == 11){
			RotateCounterclockwise(0.3,90.0);//rotate to hopper / we hit it head on for balls / to fall on the bot
		}
		else if (autonomousPhase == 12){
			DriveForward(0.7,91.6);
		}
	}
	//our spot is blue right / triggers one hopper only / we don't do a gear
	else if(autonomousChooser == 12){
		if(autonomousPhase == 0){
			DriveBackward(0.7,208.9);//drive back to hopper / rotate to face the hopper / get all of the balls
		}
		else if (autonomousPhase == 1){
			RotateCounterclockwise(0.3,90);
		}
		else if (autonomousPhase == 2){
			DriveForward(0.7,91.6);
		}
	}
	else if(autonomousChooser == 13){
		if (autonomousPhase == 0){
			DriveBackward(0.7,80.5);//gear port is on back / so we must drive backwards to / deliver the gear
		}
		else if (autonomousPhase == 1){
			RotateClockwise(0.3,45.0);//rotate clockwise to / drive to the airship to dock / pray we hit the spike
		}
		else if (autonomousPhase == 2){
			DriveBackward(0.4,32.0);
		}
		else if (autonomousPhase == 3){
			Wait(3.0);//wait for the human / why are they so very slow / let us hurry up
		}
		else if (autonomousPhase == 4){
			DriveForward(0.7,20.0);//drive back to base line / rotate to face front for once / then drive to hopper
		}
		else if (autonomousPhase == 5){
			RotateCounterclockwise(0.3,135.0);
		}
		else if (autonomousPhase == 6){
			DriveForward(0.7, 81.0);
		}
		else if (autonomousPhase == 7){
			RotateCounterclockwise(0.3,90.0);//rotate to hopper / we hit it head on for balls / to fall on the bot
		}
		else if (autonomousPhase == 8){
			DriveForward(0.7, 96.5);
		}
	}
	//our spot is red mid / triggers one hopper after / we go for the gear
	else if(autonomousChooser == 14){
		if(autonomousPhase == 0){
			DriveBackward(0.5,80.5);//gear port is on back / so we must drive backwards to / deliver the gear
		}
		else if(autonomousPhase == 1){
			Wait(3.0);//wait for the human / why are they so very slow / let us hurry up
		}
		else if(autonomousPhase == 2){
			DriveForward(0.7,40.0);//drive back to base line / rotate to face front for once / then drive to hopper
		}
		else if(autonomousPhase == 3){
			RotateCounterclockwise(0.5,90.0);
		}
		else if(autonomousPhase == 4){
			DriveForward(0.7,85.0);
		}
		else if (autonomousPhase == 5){
			RotateClockwise(0.3,90.0);
		}
		else if (autonomousPhase == 6){
			DriveForward(0.7, 250.8);
		}
		else if (autonomousPhase == 7){
			RotateCounterclockwise(0.3,90.0);//rotate to hopper / we hit it head on for balls / to fall on the bot
		}
		else if (autonomousPhase == 8){
			DriveForward(0.7,96.5);
		}
	}
	//our spot is red right / triggers one hopper after / we go for the gear
	else if (autonomousChooser == 15){
		if (autonomousPhase == 0){
			DriveBackward(0.7,80.5);//gear port is on back / so we must drive backwards to / deliver the gear
		}
		else if (autonomousPhase == 1){
			RotateCounterclockwise(0.3,45.0);//rotate clockwise to / drive to the airship to dock / pray we hit the spike
		}
		else if (autonomousPhase == 2){
			DriveBackward(0.4,20.0);
		}
		else if (autonomousPhase == 3){
			Wait(3.0);//wait for the human / why are they so very slow / let us hurry up
		}
		else if (autonomousPhase == 4){
			DriveForward(0.7,20.0);//drive back to base line / rotate to face front for once / then drive to hopper
		}
		else if (autonomousPhase == 5){
			RotateCounterclockwise(0.3,135.0);
		}
		else if (autonomousPhase == 6){
			DriveForward(0.7,91.0);
		}
		else if (autonomousPhase == 7){
			RotateClockwise(0.3,90.0);//rotate to hopper / we hit it head on for balls / to fall on the bot
		}
		else if (autonomousPhase == 8){
			DriveForward(0.7,96.5);
		}
	}
	//our spot is blue left / triggers one hopper after / we go for the gear
	else if (autonomousChooser == 16){
		if (autonomousPhase == 0){
			DriveBackward(0.7,80.5);//gear port is on back / so we must drive backwards to / deliver the gear
		}
		else if (autonomousPhase == 1){
			RotateClockwise(0.3,45.0);//rotate clockwise to / drive to the airship to dock / pray we hit the spike
		}
		else if (autonomousPhase == 2){
			DriveBackward(0.4,20.0);
		}
		else if (autonomousPhase == 3){
			Wait(3.0);//wait for the human / why are they so very slow / let us hurry up
		}
		else if (autonomousPhase == 4){
			DriveForward(0.7,20.0);//drive back to base line / rotate to face front for once / then drive to hopper
		}
		else if (autonomousPhase == 5){
			RotateClockwise(0.3,135.0);
		}
		else if (autonomousPhase == 6){
			DriveForward(0.7,81.0);
		}
		else if (autonomousPhase == 7){
			RotateCounterclockwise(0.3,90.0);//rotate to hopper / we hit it head on for balls / to fall on the bot
		}
		else if (autonomousPhase == 8){
			DriveForward(0.7,96.5);
		}
	}
	//our spot is blue mid / triggers one hopper after / we go for the gear
	else if (autonomousChooser == 17){
		if(autonomousPhase == 0){
			DriveBackward(0.5, 80.5);//gear port is on back / so we must drive backwards to / deliver the gear
		}
		else if(autonomousPhase == 1){
			Wait(3.0);//wait for the human / why are they so very slow / let us hurry up
		}
		else if(autonomousPhase == 2){
			DriveForward(0.7, 40.0);//drive back to base line / rotate to face front for once / then drive to hopper
		}
		else if(autonomousPhase == 3){
			RotateClockwise(0.5, 90.0);
		}
		else if(autonomousPhase == 4){
			DriveForward(0.7,85.0);
		}
		else if (autonomousPhase == 5){
			RotateClockwise(0.3,90.0);
		}
		else if (autonomousPhase == 6){
			DriveForward(0.7,250.8);
		}
		else if (autonomousPhase == 7){
			RotateCounterclockwise(0.3,90);//rotate to hopper / we hit it head on for balls / to fall on the bot
		}
		else if (autonomousPhase == 8){
			DriveForward(0.7,96.5);
		}
	}
	//our spot is blue right / triggers one hopper after / we go for the gear
	else if (autonomousChooser == 18){
		if (autonomousPhase == 0){
			DriveBackward(0.7,80.5);//gear port is on back / so we must drive backwards to / deliver the gear
		}
		else if (autonomousPhase == 1){
			RotateCounterclockwise(0.3,45.0);//rotate clockwise to / drive to the airship to dock / pray we hit the spike
		}
		else if (autonomousPhase == 2){
			DriveBackward(0.4,20.0);
		}
		else if (autonomousPhase == 3){
			Wait(3.0);//wait for the human / why are they so very slow / let us hurry up
		}
		else if (autonomousPhase == 4){
			DriveForward(0.7,20.0);//drive back to base line / rotate to face front for once / then drive to hopper
		}
		else if (autonomousPhase == 5){
			RotateCounterclockwise(0.3,135.0);
		}
		else if (autonomousPhase == 6){
			DriveForward(0.7, 81.0);
		}
		else if (autonomousPhase == 7){
			RotateCounterclockwise(0.3,90.0);//rotate to hopper / we hit it head on for balls / to fall on the bot
		}
		else if (autonomousPhase == 8){
			DriveForward(0.7,96.5);
		}
	}
	else if(autonomousChooser == 19){
		if (autonomousPhase == 0){
			DriveBackward(0.7,59.0);
		}
		else if (autonomousPhase == 1){
			RotateCounterclockwise(0.3,45.0);
		}
		else if (autonomousPhase == 2){
			Shoot(0.7, 10.0);
		}
	}
	else if(autonomousChooser == 20){
		if (autonomousPhase == 0){
			DriveBackward(0.7,59.0);
		}
		else if (autonomousPhase == 1){
			RotateClockwise(0.3,45.0);
		}
		else if (autonomousPhase == 2){
			Shoot(0.7, 10.0);
		}
	}
}


