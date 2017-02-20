 #include <iostream>
#include <memory>
#include <string>
#include <math.h>

#include <IterativeRobot.h>
#include <CANTalon.h>
#include <LiveWindow/LiveWindow.h>
#include <SmartDashboard/SendableChooser.h>
#include <SmartDashboard/SmartDashboard.h>

#define WHEEL_DIAM 6.0;
#define DRIVE_DIAM 28.75;
#define PULSE_PER_REV 860.0;
#define PI 3.141593;

class Robot: public frc::IterativeRobot {
public:

	CANTalon *rightFrontMotor = new CANTalon(2);
	CANTalon *rightBackMotor = new CANTalon(1);
	CANTalon *leftFrontMotor = new CANTalon(4);
	CANTalon *leftBackMotor = new CANTalon(8);

	const double wheelDiam = WHEEL_DIAM;
	const double driveDiam = DRIVE_DIAM;
	const double pulsePerRev = PULSE_PER_REV;
	const double pi = PI;

	const double pulse_per_inch  = (pulsePerRev) / (wheelDiam * pi);
	const double pulse_per_radian = (driveDiam / 2) * pulse_per_inch;

	int autonomousPhase = 0;
	int counter = 0;
	int autonomousChooser = 0;

	void DriveForward(double speed, double distance){
		double encoderValue = rightFrontMotor->GetEncPosition();
		double encoderDistance = distance * pulse_per_inch;
		if(abs(encoderValue) <= encoderDistance){
			leftFrontMotor->Set(speed);
			leftBackMotor->Set(speed);
			rightFrontMotor->Set(speed);
			rightBackMotor->Set(speed);
		}
		else if(counter <= 25){
			leftFrontMotor->Set(0.0);
			leftBackMotor->Set(0.0);
			rightFrontMotor->Set(0.0);
			rightBackMotor->Set(0.0);
			counter++;
		}
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

	void DriveBackward(double speed, double distance){
		double encoderValue = rightFrontMotor->GetEncPosition();
		double encoderDistance = distance * pulse_per_inch;
		if(abs(encoderValue) <= encoderDistance){
			leftFrontMotor->Set(-speed);
			leftBackMotor->Set(-speed);
			rightFrontMotor->Set(-speed);
			rightBackMotor->Set(-speed);
		}
		else if(counter <= 25){
			leftFrontMotor->Set(0.0);
			leftBackMotor->Set(0.0);
			rightFrontMotor->Set(0.0);
			rightBackMotor->Set(0.0);
			counter++;
			std::cout << counter << std::endl;
		}
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

	void RotateCounterClockwise(double speed, double angle){
		double encoderValue = rightFrontMotor->GetEncPosition();
		double radianAngle = angle * (pi /180);
		double encoderDistance =  radianAngle * pulse_per_radian;
		if(abs(encoderValue) <= encoderDistance){
			leftFrontMotor->Set(-speed);
			leftBackMotor->Set(-speed);
			rightFrontMotor->Set(speed);
			rightBackMotor->Set(speed);
		}
		else if(counter <= 25){
			leftFrontMotor->Set(0.0);
			leftBackMotor->Set(0.0);
			rightFrontMotor->Set(0.0);
			rightBackMotor->Set(0.0);
			counter++;
		}
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

	void RotateClockwise(double speed, double angle){
		double encoderValue = rightFrontMotor->GetEncPosition();
		double radianAngle = angle * (pi /180);
		double encoderDistance =  radianAngle * pulse_per_radian;
		if(abs(encoderValue) <= encoderDistance){
			leftFrontMotor->Set(speed);
			leftBackMotor->Set(speed);
			rightFrontMotor->Set(-speed);
			rightBackMotor->Set(-speed);
		}
		else if(counter <= 25){
			leftFrontMotor->Set(0.0);
			leftBackMotor->Set(0.0);
			rightFrontMotor->Set(0.0);
			rightBackMotor->Set(0.0);
			counter++;
		}
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

	void Wait(double time){
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

	void RobotInit() {
		rightFrontMotor->SetInverted(true);
		rightBackMotor->SetInverted(true);
		leftFrontMotor->SetFeedbackDevice(CANTalon::QuadEncoder);
		rightFrontMotor->SetFeedbackDevice(CANTalon::QuadEncoder);
		leftFrontMotor->ConfigEncoderCodesPerRev(20);
		rightFrontMotor->ConfigEncoderCodesPerRev(20);
	}

	void AutonomousInit() {
		leftFrontMotor->SetEncPosition(0);
		rightFrontMotor->SetEncPosition(0);
		autonomousPhase = 0;
		counter = 0;
		autonomousChooser = 2;
	}

	void AutonomousPeriodic() {
		//in case of encoders breaking
		if(autonomousChooser == 0){

		}
		//red left gears first
	else if(autonomousChooser == 1){
			if (autonomousPhase == 0){
				DriveBackward(0.7,110.0);//drive backward to base line
			}
			else if (autonomousPhase == 1){
				RotateClockwise(0.3,45.0);//rotate clockwise to make us facing the dock for the gear
			}
			else if (autonomousPhase == 2){
				DriveBackward(0.7,29.2);//drive backward up to the airship
			}
			else if (autonomousPhase == 3){
				Wait(3.0);//wait for human player
			}
			else if (autonomousPhase == 4){
				DriveForward(0.7,29.2);//drive forward to the base line
			}
			else if (autonomousPhase == 5){
				RotateClockwise(0.3,135.0);//rotate counter clockwise to have mouth in the front
			}
			else if (autonomousPhase == 6){
				DriveForward(0.7, 115.6);//drive forward to be ready to hit hopper right
			}
			else if (autonomousPhase == 7){
				RotateCounterClockwise(0.3,45);//rotate counter clockwise 45 degrees to face hoppers
			}
			else if (autonomousPhase == 8){
				DriveForward(0.7, 91.6);//drive up to the hopper
			}
		}
		//red center gears first
		else if(autonomousChooser == 2){
			if(autonomousPhase == 0){
				DriveBackward(0.7, 53.3);//drive backward to airship
			}
			else if(autonomousPhase == 1){
				Wait(3.0);//wait for human player to grab the gear
			}
			else if(autonomousPhase == 2){
				DriveForward(0.7, 26.65);//drive forward half way
			}
			else if(autonomousPhase == 3){
				RotateClockwise(0.5, 135.0);//rotate clockwise to have front facing the way we want
			}
			else if(autonomousPhase == 4){
				DriveForward(0.7,37.69);//drive to the middle of red left
			}
			else if (autonomousPhase == 5){
				RotateClockwise(0.3,45.0);//turn to facing the base line
			}
			else if (autonomousPhase == 6){
				DriveForward(0.7, 115.6);//drive forward to prepare for the hopper
			}
			else if (autonomousPhase == 7){
				RotateCounterClockwise(0.3,45);//rotate 45 degrees counter clockwise to face hopper
			}
			else if (autonomousPhase == 8){
				DriveForward(0.7, 91.6);//drive up to the hopper
			}
		}
		//red right gears first
		else if (autonomousChooser == 3){
			if (autonomousPhase == 0){
				DriveBackward(0.7,110.0);//drive backward to the baseline
			}
			else if (autonomousPhase == 1){
				RotateCounterClockwise(0.3,45.0);//rotate 45 degrees counter clockwise to face the airship
			}
			else if (autonomousPhase == 2){
				DriveBackward(0.7,29.2);//drive up to the airship
			}
			else if (autonomousPhase == 3){
				Wait(3.0);//wait for the human player to grab the gear
			}
			else if (autonomousPhase == 4){
				DriveForward(0.7,29.2);// return to the base line
			}
			else if (autonomousPhase == 5){
				RotateClockwise(0.3,135);//rotate 135 degrees clockwise to make the front of the robot facing to the enemy
			}
			else if (autonomousPhase == 6){
				DriveForward(0.7,34.25);// drive forward to prepare for the hopper
			}
			else if (autonomousPhase == 7){
				RotateClockwise(0.3,45);// rotate 45 degrees to face the hopper
			}
			else if (autonomousPhase == 8){
				DriveForward(0.7,91.63);//drive forward to the hopper
			}
		}
		//blue left gears first
		else if (autonomousChooser == 4){
			if (autonomousPhase == 0){
				DriveBackward(0.7,110.0);// drive up to the baseline
			}
			else if (autonomousPhase == 1){
				RotateClockwise(0.3,45.0);//rotate 45 clockwise to face the airship
			}
			else if (autonomousPhase == 2){
				DriveBackward(0.7,29.2);//drive up to the airship
			}
			else if (autonomousPhase == 3){
				Wait(3.0);//wait 3 second for the human player to grab the gear
			}
			else if (autonomousPhase == 4){
				DriveForward(0.7,29.2);//drive forward to reach the baseline
			}
			else if (autonomousPhase == 5){
				RotateClockwise(0.3,135);//rotate 135 degrees to make the front faceing the enemy
			}
			else if (autonomousPhase == 6){
				DriveForward(0.7,34.25);//drive forward to prepare to drive to the hopper
			}
			else if (autonomousPhase == 7){
				RotateCounterClockwise(0.3,45);//rotate 45 degrees counter clockwise to face the hopper
			}
			else if (autonomousPhase == 8){
				DriveForward(0.7,91.63);//drive up to the hopper
			}
		}
		//blue center gears first
		else if (autonomousChooser == 5){
			if(autonomousPhase == 0){
				DriveBackward(0.7, 53.3);//drive backward to airship
			}
			else if(autonomousPhase == 1){
				Wait(3.0);//wait for human player to grab the gear
			}
			else if(autonomousPhase == 2){
				DriveForward(0.7, 26.65);//drive forward half way
			}
			else if(autonomousPhase == 3){
				RotateClockwise(0.5, 135.0);//rotate clockwise to have front facing the way we want
			}
			else if(autonomousPhase == 4){
				DriveForward(0.7,37.69);//drive to the middle of red left
			}
			else if (autonomousPhase == 5){
				RotateClockwise(0.3,45.0);//turn to facing the base line
			}
			else if (autonomousPhase == 6){
				DriveForward(0.7,34.25);//drive forward to prepare for the hopper
			}
			else if (autonomousPhase == 7){
				RotateCounterClockwise(0.3,45);//rotate 45 degrees counter clockwise to face the hopper
			}
			else if (autonomousPhase == 8){
				DriveForward(0.7,91.63);//drive up to the hopper
			}
		}
		//blue right gears first
		else if (autonomousChooser == 6){
			if (autonomousPhase == 0){
				DriveBackward(0.7,110.0);//drive backward to base line
			}
			else if (autonomousPhase == 1){
				RotateCounterClockwise(0.3,45.0);//rotate clockwise to make us facing the dock for the gear
			}
			else if (autonomousPhase == 2){
				DriveBackward(0.7,29.2);//drive backward up to the airship
			}
			else if (autonomousPhase == 3){
				Wait(3.0);//wait for human player
			}
			else if (autonomousPhase == 4){
				DriveForward(0.7,29.2);//drive forward to the base line
			}
			else if (autonomousPhase == 5){
				RotateCounterClockwise(0.3,135.0);//rotate counter clockwise to have mouth in the front
			}
			else if (autonomousPhase == 6){
				DriveForward(0.7, 115.6);//drive forward to prepare to hit the hopper
			}
			else if (autonomousPhase == 7){
				RotateClockwise(0.3,45);//rotate 45 degrees to face the hopper
			}
			else if (autonomousPhase == 8){
				DriveForward(0.7, 91.6);//drive up to the hopper
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
				RotateCounterClockwise(0.3,90.0);//rotate 90 degrees
			}
			else if (autonomousPhase == 2){
				DriveForward(0.7,70.3);//drive forward to the middle of red right
			}
			else if (autonomousPhase == 3){
				RotateCounterClockwise(0.3,90.0);//rotate 90 degrees
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
				RotateCounterClockwise(0.3,90.0);//rotate 90 degress to face the hopper
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
				RotateCounterClockwise(0.3,90.0);//rotate 90 degrees
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
				RotateCounterClockwise(0.3,90.0);//rotate 90 degrees
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
				RotateCounterClockwise(0.3,90.0);//rotate 90 degress to face the hopper
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
				RotateCounterClockwise(0.3,90.0);//rotate 90 degrees to face the hopper
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
				RotateCounterClockwise(0.3,90.0);//rotate 90 degress to face the hopper
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
				RotateCounterClockwise(0.3,90);//rotate 90 degrees to face the hopper
			}
			else if (autonomousPhase == 2){
				DriveForward(0.7,91.6);//drive forward to hit the hopper
			}
		}
	}

	void TeleopInit() {

	}

	void TeleopPeriodic() {

	}

	void TestPeriodic() {

	}
};

START_ROBOT_CLASS(Robot)
