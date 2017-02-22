/*
 * Dashboard.cpp
 *
 *  Created on: Feb 18, 2017
 *      Author: Zack
 */
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
	if(cam.GetName() != "Camera"){
		cam = CameraServer::GetInstance()->StartAutomaticCapture("Camera", "/dev/video0");
		cam.SetBrightness(25);
		cam.SetResolution(640, 480);
	}
}

int Dashboard::AutoSelect(){
	DriverStation &drive = DriverStation::GetInstance();
	bool hopperFirst = SmartDashboard::GetBoolean("DB/Button 0", false);
	bool shoot = SmartDashboard::GetBoolean("DB/Button 1", false);
	bool disable = SmartDashboard::GetBoolean("DB/Button 3", false);
	if(disable == true){
		return 0;
	}
	else {
		if(shoot == false){
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
		}
		else if(shoot == true){
			if(drive.GetAlliance() == DriverStation::Alliance::kRed){
				return 13;
			}
			else if(drive.GetAlliance() == DriverStation::Alliance::kBlue){
				return 14;
			}
		}
	}

	return 0; //default return, if none of the others trigger
}




