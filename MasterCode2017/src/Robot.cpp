#include <Climber.h>
#include <iostream>
#include <memory>
#include <string>

#include <Drive.h>
#include <Feeder.h>
#include <Intake.h>
#include <Shooter.h>
#include <Climber.h>
#include <IterativeRobot.h>
#include <LiveWindow/LiveWindow.h>
#include <SmartDashboard/SendableChooser.h>
#include <SmartDashboard/SmartDashboard.h>

class Robot: public frc::IterativeRobot {
public:

	Drive drive;
	Feeder feeder;
	Intake intake;
	Shooter shooter;
	Climber climber;

	void RobotInit() {
		drive.DriveInit();
		feeder.FeederInit();
		intake.IntakeInit();
		shooter.ShooterInit();
		climber.ClimberInit();
	}

	void AutonomousInit() {

	}

	void AutonomousPeriodic() {

	}

	void TeleopInit() {

	}

	void TeleopPeriodic() {
		drive.DriveTeleopPeriodic();
		feeder.FeederTeleopPeriodic();
		intake.IntakeTeleopPeriodic();
		shooter.ShooterTeleopPeriodic();
		climber.ClimberTeleopPeriodic();
	}

	void TestPeriodic() {

	}
};

START_ROBOT_CLASS(Robot)
