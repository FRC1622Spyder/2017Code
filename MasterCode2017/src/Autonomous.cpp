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
#include <LiveWindow/LiveWindow.h>
#include <SmartDashboard/SendableChooser.h>
#include <SmartDashboard/SmartDashboard.h>

//-1 <= speed <= 1; distance in inches
void Autonomous::DriveForward(double speed, double distance){
	//periodic--updates every 200 ms
	//get the encoder position
	double encoderValue = leftFrontMotor->GetEncPosition();
	//multiply the final distance by the conversion factor
	double encoderDistance = distance * pulse_per_inch;
	//move robot while the encoder is less than total distance
	if(abs(encoderValue) <= encoderDistance){
		leftFrontMotor->Set(speed);
		leftBackMotor->Set(speed);
		rightFrontMotor->Set(speed);
		rightBackMotor->Set(speed);
	}
	//pause for 25 periods (0.5 seconds)
	else if(counter <= 25){
		leftFrontMotor->Set(0.0);
		leftBackMotor->Set(0.0);
		rightFrontMotor->Set(0.0);
		rightBackMotor->Set(0.0);
		counter++;
	}
	//reset variables and increment autonomous phase
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

//-1 <= speed <= 1; distance in inches
void Autonomous::DriveBackward(double speed, double distance){
	//periodic--updates every 200 ms
	//get the encoder position
	double encoderValue = leftFrontMotor->GetEncPosition();
	//multiply the final distance by the conversion factor
	double encoderDistance = distance * pulse_per_inch;
	//move robot while the encoder is less than total distance
	if(abs(encoderValue) <= encoderDistance){
		leftFrontMotor->Set(-speed);
		leftBackMotor->Set(-speed);
		rightFrontMotor->Set(-speed);
		rightBackMotor->Set(-speed);
	}
	//pause for 25 periods (0.5 seconds)
	else if(counter <= 25){
		leftFrontMotor->Set(0.0);
		leftBackMotor->Set(0.0);
		rightFrontMotor->Set(0.0);
		rightBackMotor->Set(0.0);
		counter++;
	}
	//reset variables and increment autonomous phase
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

////-1 <= speed <= 1; angle in degrees
void Autonomous::RotateCounterclockwise(double speed, double angle){
	//periodic--updates every 200 ms
	//get encoder position
	double encoderValue = leftFrontMotor->GetEncPosition();
	//convert angle to radians
	double radianAngle = angle * (pi /180);
	//multiply angle by conversion factor
	double encoderDistance =  radianAngle * pulse_per_radian;
	//move robot while the encoder is less than total distance
	if(abs(encoderValue) <= encoderDistance){
		leftFrontMotor->Set(-speed);
		leftBackMotor->Set(-speed);
		rightFrontMotor->Set(speed);
		rightBackMotor->Set(speed);
	}
	//wait for 25 periods (0.5 seconds)
	else if(counter <= 25){
		leftFrontMotor->Set(0.0);
		leftBackMotor->Set(0.0);
		rightFrontMotor->Set(0.0);
		rightBackMotor->Set(0.0);
		counter++;
	}
	//reset variables and increment autonomous phase
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

//-1 <= speed <= 1; angle in degrees
void Autonomous::RotateClockwise(double speed, double angle){
	//periodic--updates every 200 ms
	//get encoder value
	double encoderValue = leftFrontMotor->GetEncPosition();
	//convert angle to radians
	double radianAngle = angle * (pi /180);
	//multiply angle by conversion factor
	double encoderDistance =  radianAngle * pulse_per_radian;
	//move robot while the encoder is less than total distance
	if(abs(encoderValue) <= encoderDistance){
		leftFrontMotor->Set(speed);
		leftBackMotor->Set(speed);
		rightFrontMotor->Set(-speed);
		rightBackMotor->Set(-speed);
	//wait for 25 periods (0.5 seconds)
	}
	else if(counter <= 25){
		leftFrontMotor->Set(0.0);
		leftBackMotor->Set(0.0);
		rightFrontMotor->Set(0.0);
		rightBackMotor->Set(0.0);
		counter++;
	}
	//reset variables and increment autonomous phase
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

//time in seconds
void Autonomous::Wait(double time){
	//convert time to periods
	double periods = time * 50;
	//wait for the specified number of periods
	if(counter <= periods){
		leftFrontMotor->Set(0.0);
		leftBackMotor->Set(0.0);
		rightFrontMotor->Set(0.0);
		rightBackMotor->Set(0.0);
		counter++;
	}
	//reset variables and increment autonomous phase
	else{
		counter = 0;
		autonomousPhase++;
	}
}

void Autonomous::AutonomousInit(){
	//declare motors
	leftBackMotor = new CANTalon(4);//8 on the test robot, 3 on actual robot
	leftFrontMotor = new CANTalon(3);
	rightBackMotor = new CANTalon(2);
	rightFrontMotor = new CANTalon(1);

	//invert right side motors
	rightBackMotor->SetInverted(true);
	rightFrontMotor->SetInverted(true);

	//set encoder type to QuadEncoder
	leftFrontMotor->SetFeedbackDevice(CANTalon::QuadEncoder);
	rightFrontMotor->SetFeedbackDevice(CANTalon::QuadEncoder);

	//set encoder codes per revolution to 20
	leftFrontMotor->ConfigEncoderCodesPerRev(20);
	rightFrontMotor->ConfigEncoderCodesPerRev(20);

	//reset encoders
	leftFrontMotor->SetEncPosition(0);
	rightFrontMotor->SetEncPosition(0);

	//create a dashboard object
	Dashboard dashboard;
	//reset variables
	autonomousPhase = 0;
	counter = 0;
	//select the autonomous using the AutoSelect function from the dashboard object
	autonomousChooser = dashboard.AutoSelect();
}

void Autonomous::AutonomousPeriodic(){
	//in case of encoders breaking
	if(autonomousChooser == 0){

	}
	//red left gears first
	else if(autonomousChooser == 1){
		if (autonomousPhase == 0){
			DriveBackward(0.7,80.5);//drive backward to base line
		}
		else if (autonomousPhase == 1){
			RotateClockwise(0.3,45.0);//rotate clockwise to make us facing the dock for the gear
		}
		else if (autonomousPhase == 2){
			DriveBackward(0.7,32.0);//drive backward up to the airship
		}
		else if (autonomousPhase == 3){
			Wait(3.0);//wait for human player
		}
		else if (autonomousPhase == 4){
			DriveForward(0.7,32.0);//drive forward to the base line
		}
		else if (autonomousPhase == 5){
			RotateClockwise(0.3,135.0);//rotate counter clockwise to have mouth in the front
		}
		else if (autonomousPhase == 6){
			DriveForward(0.7, 81.0);//drive forward to be ready to hit hopper right
		}
		else if (autonomousPhase == 7){
			RotateCounterclockwise(0.3,90.0);//rotate counter clockwise 45 degrees to face hoppers
		}
		else if (autonomousPhase == 8){
			DriveForward(0.7, 96.5);//drive up to the hopper
		}
	}
	//red center gears first
	else if(autonomousChooser == 2){
		if(autonomousPhase == 0){
			DriveBackward(0.7,80.5);//drive backward to airship
		}
		else if(autonomousPhase == 1){
			Wait(3.0);//wait for human player to grab the gear
		}
		else if(autonomousPhase == 2){
			DriveForward(0.7,40.0);//drive forward half way
		}
		else if(autonomousPhase == 3){
			RotateClockwise(0.5,135.0);//rotate clockwise to have front facing the way we want
		}
		else if(autonomousPhase == 4){
			DriveForward(0.7,85.0);//drive to the middle of red left
		}
		else if (autonomousPhase == 5){
			RotateClockwise(0.3,45.0);//turn to facing the base line
		}
		else if (autonomousPhase == 6){
			DriveForward(0.7, 250.8);//drive forward to prepare for the hopper
		}
		else if (autonomousPhase == 7){
			RotateCounterclockwise(0.3,90.0);//rotate 45 degrees counter clockwise to face hopper
		}
		else if (autonomousPhase == 8){
			DriveForward(0.7,96.5);//drive up to the hopper
		}
	}
	//red right gears first
	else if (autonomousChooser == 3){
		if (autonomousPhase == 0){
			DriveBackward(0.7,80.5);//drive backward to the baseline
		}
		else if (autonomousPhase == 1){
			RotateCounterclockwise(0.3,45.0);//rotate 45 degrees counter clockwise to face the airship
		}
		else if (autonomousPhase == 2){
			DriveBackward(0.7,32.0);//drive up to the airship
		}
		else if (autonomousPhase == 3){
			Wait(3.0);//wait for the human player to grab the gear
		}
		else if (autonomousPhase == 4){
			DriveForward(0.7,32.0);// return to the base line
		}
		else if (autonomousPhase == 5){
			RotateClockwise(0.3,135);//rotate 135 degrees clockwise to make the front of the robot facing to the enemy
		}
		else if (autonomousPhase == 6){
			DriveForward(0.7,91.0);// drive forward to prepare for the hopper
		}
		else if (autonomousPhase == 7){
			RotateClockwise(0.3,90.0);// rotate 45 degrees to face the hopper
		}
		else if (autonomousPhase == 8){
			DriveForward(0.7,96.5);//drive forward to the hopper
		}
	}
	//blue left gears first
	else if (autonomousChooser == 4){
		if (autonomousPhase == 0){
			DriveBackward(0.7,80.5);// drive up to the baseline
		}
		else if (autonomousPhase == 1){
			RotateClockwise(0.3,45.0);//rotate 45 clockwise to face the airship
		}
		else if (autonomousPhase == 2){
			DriveBackward(0.7,32.0);//drive up to the airship
		}
		else if (autonomousPhase == 3){
			Wait(3.0);//wait 3 second for the human player to grab the gear
		}
		else if (autonomousPhase == 4){
			DriveForward(0.7,32.0);//drive forward to reach the baseline
		}
		else if (autonomousPhase == 5){
			RotateClockwise(0.3,135.0);//rotate 135 degrees to make the front faceing the enemy
		}
		else if (autonomousPhase == 6){
			DriveForward(0.7,81.0);//drive forward to prepare to drive to the hopper
		}
		else if (autonomousPhase == 7){
			RotateCounterclockwise(0.3,45);//rotate 45 degrees counter clockwise to face the hopper
		}
		else if (autonomousPhase == 8){
			DriveForward(0.7,96.5);//drive up to the hopper
		}
	}
	//blue center gears first
	else if (autonomousChooser == 5){
		if(autonomousPhase == 0){
			DriveBackward(0.7, 80.5);//drive backward to airship
		}
		else if(autonomousPhase == 1){
			Wait(3.0);//wait for human player to grab the gear
		}
		else if(autonomousPhase == 2){
			DriveForward(0.7, 40.0);//drive forward half way
		}
		else if(autonomousPhase == 3){
			RotateClockwise(0.5, 135.0);//rotate clockwise to have front facing the way we want
		}
		else if(autonomousPhase == 4){
			DriveForward(0.7,85.0);//drive to the middle of red left
		}
		else if (autonomousPhase == 5){
			RotateClockwise(0.3,45.0);//turn to facing the base line
		}
		else if (autonomousPhase == 6){
			DriveForward(0.7,250.8);//drive forward to prepare for the hopper
		}
		else if (autonomousPhase == 7){
			RotateCounterclockwise(0.3,45);//rotate 45 degrees counter clockwise to face the hopper
		}
		else if (autonomousPhase == 8){
			DriveForward(0.7,96.5);//drive up to the hopper
		}
	}
	//blue right gears first
	else if (autonomousChooser == 6){
		if (autonomousPhase == 0){
			DriveBackward(0.7,80.5);//drive backward to base line
		}
		else if (autonomousPhase == 1){
			RotateCounterclockwise(0.3,45.0);//rotate clockwise to make us facing the dock for the gear
		}
		else if (autonomousPhase == 2){
			DriveBackward(0.7,32.0);//drive backward up to the airship
		}
		else if (autonomousPhase == 3){
			Wait(3.0);//wait for human player
		}
		else if (autonomousPhase == 4){
			DriveForward(0.7,32.0);//drive forward to the base line
		}
		else if (autonomousPhase == 5){
			RotateCounterclockwise(0.3,135.0);//rotate counter clockwise to have mouth in the front
		}
		else if (autonomousPhase == 6){
			DriveForward(0.7, 81.0);//drive forward to prepare to hit the hopper
		}
		else if (autonomousPhase == 7){
			RotateClockwise(0.3,45);//rotate 45 degrees to face the hopper
		}
		else if (autonomousPhase == 8){
			DriveForward(0.7, 95.6);//drive up to the hopper
		}
	}
	//red left
	if(autonomousChooser == 7){
		if(autonomousPhase == 0){
			DriveBackward(0.7,208.9);//drive backward to prepare to hit the first hopper
		}
		else if (autonomousPhase == 1){
			RotateClockwise(0.3,90);//rotate 90 degrees to face the hopper
		}
		else if (autonomousPhase == 2){
			DriveForward(0.7,91.6);//drive forward to hit the hopper
		}
	}
	//red center
	else if(autonomousChooser == 8){

		if(autonomousPhase == 0){
			DriveBackward(0.7,46.7);//drive forward to prepare to turn
		}
		else if (autonomousPhase == 1){
			RotateCounterclockwise(0.3,90.0);//rotate 90 degrees
		}
		else if (autonomousPhase == 2){
			DriveForward(0.7,70.3);//drive forward to the middle of red right
		}
		else if (autonomousPhase == 3){
			RotateCounterclockwise(0.3,90.0);//rotate 90 degrees
		}
		else if (autonomousPhase == 4){
			DriveForward(0.7,34.3);//drive forward to prepare for the first hopper
		}
		else if (autonomousPhase == 5){
			RotateClockwise(0.3,90.0);//rotate 90 degrees to face the hopper
		}
		else if (autonomousPhase == 6){
			DriveForward(0.7,91.6);//drive forward to hit the hopper
		}
		else if (autonomousPhase == 7){
			Wait(3.0);//wait 3 seconds for balls to flow out
		}
		else if (autonomousPhase == 8){
			DriveBackward(0.7,91.6);//drive backward to return to the middle of the right
		}
		else if (autonomousPhase == 9){
			RotateClockwise(0.3,90.0);//rotate 90 degrees
		}
		else if (autonomousPhase == 10){
			DriveForward(0.7, 240.3);//drive forward for the next hopper
		}
		else if (autonomousPhase == 11){
			RotateCounterclockwise(0.3,90.0);//rotate 90 degress to face the hopper
		}
		else if (autonomousPhase == 12){
			DriveForward(0.7,91.6);//drive forward to hit the hopper
		}
	}

	//red right
	else if(autonomousChooser == 9){
		if(autonomousPhase == 0){
			DriveBackward(0.7,81.0);//drive forward to prepare for the first hopper
		}
		else if (autonomousPhase == 1){
			RotateCounterclockwise(0.3,90.0);//rotate 90 degrees
		}
		else if (autonomousPhase == 2){
			DriveForward(0.7,91.6);//drive forward to hit the hopper
		}
		else if (autonomousPhase == 3){
			Wait(3.0);//wait 3 seconds for balls to flow out
		}
		else if (autonomousPhase == 4){
			DriveBackward(0.7,91.6);//drive backward to return to the middle of the right
		}
		else if (autonomousPhase == 5){
			RotateCounterclockwise(0.3,90.0);//rotate 90 degrees
		}
		else if (autonomousPhase == 6){
			DriveForward(0.7, 240.3);//drive forward for the next hopper
		}
		else if (autonomousPhase == 7){
			RotateClockwise(0.3,90.0);//rotate 90 degress to face the hopper
		}
		else if (autonomousPhase == 8){
			DriveForward(0.7,91.6);//drive forward to hit the hopper
		}
	}
	//blue left
	else if(autonomousChooser == 10){
		if(autonomousPhase == 0){
			DriveBackward(0.7,81.0);//drive forward to prepare for the first hopper
		}
		else if (autonomousPhase == 1){
			RotateClockwise(0.3,90.0);//rotate 90 degrees
		}
		else if (autonomousPhase == 2){
			DriveForward(0.7,91.6);//drive forward to hit the hopper
		}
		else if (autonomousPhase == 3){
			Wait(3.0);//wait 3 seconds for balls to flow out
		}
		else if (autonomousPhase == 4){
			DriveBackward(0.7,91.6);//drive backward to return to the middle of the right
		}
		else if (autonomousPhase == 5){
			RotateClockwise(0.3,90.0);//rotate 90 degrees
		}
		else if (autonomousPhase == 6){
			DriveForward(0.7, 240.3);//drive forward for the next hopper
		}
		else if (autonomousPhase == 7){
			RotateCounterclockwise(0.3,90.0);//rotate 90 degress to face the hopper
		}
		else if (autonomousPhase == 8){
			DriveForward(0.7,91.6);//drive forward to hit the hopper
		}
	}
	//blue center
	else if(autonomousChooser == 11){
		if(autonomousPhase == 0){
			DriveBackward(0.7,46.7);//drive forward to prepare to turn
		}
		else if (autonomousPhase == 1){
			RotateClockwise(0.3,90.0);//rotate 90 degrees
		}
		else if (autonomousPhase == 2){
			DriveForward(0.7,70.3);//drive forward to the middle of red right
		}
		else if (autonomousPhase == 3){
			RotateClockwise(0.3,90.0);//rotate 90 degrees to face the base line
		}
		else if (autonomousPhase == 4){
			DriveForward(0.7,34.3);//drive forward to prepare for the first hopper
		}
		else if (autonomousPhase == 5){
			RotateCounterclockwise(0.3,90.0);//rotate 90 degrees to face the hopper
		}
		else if (autonomousPhase == 6){
			DriveForward(0.7,91.6);//drive forward to hit the hopper
		}
		else if (autonomousPhase == 7){
			Wait(3.0);//wait 3 seconds for balls to flow out
		}
		else if (autonomousPhase == 8){
			DriveBackward(0.7,91.6);//drive backward to return to the middle of the right
		}
		else if (autonomousPhase == 9){
			RotateClockwise(0.3,90.0);//rotate 90 degrees
		}
		else if (autonomousPhase == 10){
			DriveForward(0.7, 240.3);//drive forward for the next hopper
		}
		else if (autonomousPhase == 11){
			RotateCounterclockwise(0.3,90.0);//rotate 90 degress to face the hopper
		}
		else if (autonomousPhase == 12){
			DriveForward(0.7,91.6);//drive forward to hit the hopper
		}
	}
	//blue right
	else if(autonomousChooser == 12){
		if(autonomousPhase == 0){
			DriveBackward(0.7,208.9);//drive backward to prepare to hit the first hopper
		}
		else if (autonomousPhase == 1){
			RotateCounterclockwise(0.3,90);//rotate 90 degrees to face the hopper
		}
		else if (autonomousPhase == 2){
			DriveForward(0.7,91.6);//drive forward to hit the hopper
		}
	}
}


