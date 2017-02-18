#include <iostream>
#include <memory>
#include <string>

#include <CameraServer.h>
#include <IterativeRobot.h>
#include <LiveWindow/LiveWindow.h>
#include <SmartDashboard/SendableChooser.h>
#include <SmartDashboard/SmartDashboard.h>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/core/core.hpp>
#include <CameraServer.h>
#include <DriverStation.h>

class Robot: public frc::IterativeRobot {
private:
	cs::UsbCamera cam;

public:

	void CameraInit(){
		if(cam.GetName() != "Camera"){
			cam = CameraServer::GetInstance()->StartAutomaticCapture("Camera", "/dev/video0");
			cam.SetBrightness(25);
			cam.SetResolution(640, 480);
		}
	}

	int AutoSelect(){
		DriverStation &drive = DriverStation::GetInstance();
		bool hopperFirst = SmartDashboard::GetBoolean("DB/Button 0", false);
		if(hopperFirst == false){
			if(drive.GetAlliance() == DriverStation::Alliance::kRed){
				if(drive.GetLocation() == 1){
					return 1;
				}
				else if(drive.GetLocation() == 2){
					return 2;
				}
				else if(drive.GetLocation() == 3){
					return 3;
				}
			}
			else if(drive.GetAlliance() == DriverStation::Alliance::kBlue){
				if(drive.GetLocation() == 1){
					return 4;
				}
				else if(drive.GetLocation() == 2){
					return 5;
				}
				else if(drive.GetLocation() == 3){
					return 6;
				}
			}
		}
		else{
			if(drive.GetAlliance() == DriverStation::Alliance::kRed){
				if(drive.GetLocation() == 1){
					return 7;
				}
				else if(drive.GetLocation() == 2){
					return 8;
				}
				else if(drive.GetLocation() == 3){
					return 9;
				}
			}
			else if(drive.GetAlliance() == DriverStation::Alliance::kBlue){
				if(drive.GetLocation() == 1){
					return 10;
				}
				else if(drive.GetLocation() == 2){
					return 11;
				}
				else if(drive.GetLocation() == 3){
					return 12;
				}
			}
		}

		return 0; //default return, if none of the others trigger
	}

	void RobotInit() {
	}

	void AutonomousInit() {
		CameraInit();
		std::cout << AutoSelect() << std::endl;
	}

	void AutonomousPeriodic() {

	}

	void TeleopInit() {

	}

	void TeleopPeriodic() {

	}

	void TestPeriodic() {

	}

	void DisabledInit(){

	}
};

START_ROBOT_CLASS(Robot)
