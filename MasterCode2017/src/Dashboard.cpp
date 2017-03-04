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
	//if a camera doesn't already exist, create a camera
	if(cam.GetName() != "Camera"){
		//create a camera that automatically sends images to the dashboard
		cam = CameraServer::GetInstance()->StartAutomaticCapture("Camera", "/dev/video0");
		//set the camera brightness
		cam.SetBrightness(25);
		//set the camera resolution
		cam.SetResolution(640, 480);
	}
}

int Dashboard::AutoSelect(){
	//create a pointer to the driver station
	DriverStation &drive = DriverStation::GetInstance();
	//get button values from the dashboard
	bool hopperFirst = SmartDashboard::GetBoolean("DB/Button 0", false);
	bool shoot = SmartDashboard::GetBoolean("DB/Button 1", false);
	bool disable = SmartDashboard::GetBoolean("DB/Button 3", false);
	//if the autonomous should be disabled, return 0
	if(disable == true){
		return 0;
	}
	//if the autonomous should be disables, run through all of the options
	else {
		//if the autonomous does not shoot, run through the hopper options
		if(shoot == false){
			//if the hopper should not be reached first, run through the gear options
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
			//if the hopper should be reached first, run through the hopper options
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
		//if autonomous should shoot, run through shooting options
		else{
			if(drive.GetAlliance() == DriverStation::Alliance::kRed){
				return 13;
			}
			else if(drive.GetAlliance() == DriverStation::Alliance::kBlue){
				return 14;
			}
		}
	}
	//default return, if none of the others trigger
	return 0;
}




