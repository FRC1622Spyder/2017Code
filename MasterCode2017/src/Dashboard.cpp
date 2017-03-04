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
#include <DriverStation.h>
#include <Dashboard.h>

void Dashboard::DashboardInit(){
	//if no camera / you should make a camera / so drivers can see 
	if(cam.GetName() != "Camera"){
		//create camera / that automatically / sends pics to dashboard
		cam = CameraServer::GetInstance()->StartAutomaticCapture("Camera", "/dev/video0");
		//set the camera / brightness twenty five percent / so it's not too bright 
		cam.SetBrightness(25);
		//set resolution / or pixels on the dashboard / in four eighty p 
		cam.SetResolution(640, 480);
	}
}

int Dashboard::AutoSelect(){
	//create a pointer / it points to driver station / and gives us data
	DriverStation &drive = DriverStation::GetInstance();
	//get button values / it gets them from the dashboard / for all of these things
	bool hopperFirst = SmartDashboard::GetBoolean("DB/Button 0", false);
	bool shoot = SmartDashboard::GetBoolean("DB/Button 1", false);
	bool disable = SmartDashboard::GetBoolean("DB/Button 3", false);
	//if autonomous / happens to be disabled / it returns zero 
	if(disable == true){
		return 0;
	}
	//if autonomous / does not request disabled / run through all options
	else {
		//if autonomous / function does not have shooting / run through hopper code
		if(shoot == false){
			//if hopper not first / run through all the gear options / there are six of them
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
			//if hopper comes first / run through the hopper options / there are also six
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
		}
		//if autonomous / does include shooting functions / run through those options 
		else{
			if(drive.GetAlliance() == DriverStation::Alliance::kRed){
				return 13;
			}
			else if(drive.GetAlliance() == DriverStation::Alliance::kBlue){
				return 14;
			}
		}
	}
	//the default return / if none of others trigger / it returns zero 
	return 0;
}




