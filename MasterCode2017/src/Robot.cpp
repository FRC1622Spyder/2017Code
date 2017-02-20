#include <iostream>
#include <memory>
#include <string>

#include <Drive.h>
#include <Feeder.h>
#include <Intake.h>
#include <Shooter.h>
#include <Climber.h>
#include <Dashboard.h>
#include <Autonomous.h>
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
	Dashboard dashboard;
	Autonomous autonomous;

	void RobotInit() {
		drive.DriveInit();
		feeder.FeederInit();
		intake.IntakeInit();
		shooter.ShooterInit();
		climber.ClimberInit();
		dashboard.DashboardInit();
	}

	void AutonomousInit() {
		autonomous.AutonomousInit();
	}

	void AutonomousPeriodic() {
		autonomous.AutonomousPeriodic();
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
