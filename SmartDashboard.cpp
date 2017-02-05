#include <CANTalon.h>
#include <IterativeRobot.h>
#include <Joystick.h>
#include <LiveWindow/LiveWindow.h>
#include <RobotDrive.h>
#include <Preferences.h>
#include <string>
#include <DriverStation.h>
#include <Camera.h>




class Robot: public frc::IterativeRobot {

public:
	double c = 0;
	std::string save;
	DriverStation& drive = DriverStation::GetInstance();
	//Camera *cam = new Camera;

	Robot() {

		//cam->makeCamera();
		SmartDashboard::PutString("Auto", "default");
		SmartDashboard::PutNumber("rightFrontMotor", 1);
		SmartDashboard::PutNumber("rightBackMotor", 2);
		SmartDashboard::PutNumber("leftFrontMotor", 3);
		SmartDashboard::PutNumber("leftBackMotor", 4);
		SmartDashboard::PutNumber("CurRPM", 0);
		SmartDashboard::PutNumber("setRPM", 20);



	}

	int AutoSelect()
	{
		save = SmartDashboard::GetString("Auto", "default");
		if(drive.GetAlliance() == DriverStation::Alliance::kRed)
		{
			if(drive.GetLocation() == 1)
			{
				return 1;
			}
			if(drive.GetLocation() == 2)
			{
				return 2;
			}
			if(drive.GetLocation() == 3)
			{
				return 3;
			}
		}
		if(drive.GetAlliance() == DriverStation::Alliance::kBlue)
		{
			if(drive.GetLocation() == 1)
			{
				return 4;
			}
			if(drive.GetLocation() == 2)
			{
				return 5;
			}
			if(drive.GetLocation() == 3)
			{
				return 6;
			}
		}

		return 0;
	}


	void AutonomousInit() override {

	}

	void AutonomousPeriodic() override {

		SmartDashboard::PutNumber("CurRPM", c);
		std::cout << c << std::endl;
		c += .1;



	}

};

START_ROBOT_CLASS(Robot)

