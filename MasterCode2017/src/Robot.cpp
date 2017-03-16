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
#include <Config.h>
#include <IterativeRobot.h>
#include <LiveWindow/LiveWindow.h>
#include <SmartDashboard/SendableChooser.h>
#include <SmartDashboard/SmartDashboard.h>

class Robot: public frc::IterativeRobot {
public:

	//declares the objects / that represent subsystems / within all our code
	Drive drive;
	Feeder feeder;
	Intake intake;
	Shooter shooter;
	Climber climber;
	Dashboard dashboard;
	Autonomous autonomous;
	Config config;

	void RobotInit() {
		//run init functions / for all of the subsystems / so robot might work
		config.ConfigInit();
		drive.DriveInit();
		feeder.FeederInit();
		intake.IntakeInit();
		shooter.ShooterInit();
		climber.ClimberInit();
		//dashboard.DashboardInit();
	}

	void AutonomousInit() {
		//autonomous start / includes the autoselect / to choose which option
		autonomous.AutonomousInit();
	}

	void AutonomousPeriodic() {
		//runs autonomous / but it's in periodic / so robot will move
		autonomous.AutonomousPeriodic();
	}

	void TeleopInit() {

	}

	void TeleopPeriodic() {
		//runs the teleop / periodic functions of / every subsystem
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
