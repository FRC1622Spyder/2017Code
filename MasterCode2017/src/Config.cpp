#include <iostream>
#include <fstream>
#include <memory>
#include <string>

#include <Config.h>
#include <NetworkTables/NetworkTable.h>

void Config::ConfigInit(){
	//a variable / it's for the network table / called ConfigTable
	//table->SetServerMode();
	//table->SetTeam(1622);
	table = NetworkTable::GetTable("ConfigTable");

	//sets default values / because it would be bad if / they didn't exist
    table->PutNumber("LeftFrontMotor", 3);
    table->PutNumber("LeftBackMotor", 4);
    table->PutNumber("RightFrontMotor", 1);
    table->PutNumber("RightBackMotor", 2);
    table->PutNumber("IntakeMotor", 6);
    table->PutNumber("FeederMotor", 5);
    table->PutNumber("ShooterMotor", 8);
    table->PutNumber("ClimberMotor", 7);
    table->PutNumber("LeftAnalog", 1);
    table->PutNumber("RightAnalog", 3);
    table->PutNumber("HalfSpeedToggle", 1);
    table->PutNumber("IntakeInButton", 1);
    table->PutNumber("IntakeOutButton", 4);
    table->PutNumber("FeederButton", 6);
    table->PutNumber("ShooterToggle", 5);
    table->PutNumber("ShooterIncreaseSpeed", 0);
    table->PutNumber("ShooterDecreaseSpeed", 180);
    table->PutNumber("ClimberButton", 3);
}

int Config::GetMotorPort(Config::MOTOR motor){
	int port;
	//depending on which / motor port is requested / finds out which motor
	//uses network table / to find and return the port / as an integer
	if(motor == LeftFrontMotor){
		port = (int) table->GetNumber("LeftFrontMotor", 3);
		return port;
	}
	else if(motor == LeftBackMotor){
		port = (int) table->GetNumber("LeftBackMotor", 4);
		return port;
	}
	else if(motor == RightFrontMotor){
		port = (int) table->GetNumber("RightFrontMotor", 1);
		return port;
	}
	else if(motor == RightBackMotor){
		port = (int) table->GetNumber("RightBackMotor", 2);
		return port;
	}
	else if(motor == IntakeMotor){
		port = (int) table->GetNumber("IntakeMotor", 6);
		return port;
	}
	else if(motor == FeederMotor){
		port = (int) table->GetNumber("FeederMotor", 5);
		return port;
	}
	else if(motor == ShooterMotor){
		port = (int) table->GetNumber("ShooterMotor", 8);
		return port;
	}
	else if(motor == ClimberMotor){
		port = (int) table->GetNumber("ClimberMotor", 7);
		return port;
	}
	//if motor unknown / return is negative one / so things don't screw up
	return -1;
}

int Config::GetControlMapping(MAPPING mapping){
	int map;
	//finds out the button / that is used on the joystick / that we need to map
	if(mapping == LeftAnalogMapping){
		map = (int) table->GetNumber("LeftAnalog", 1);
		return map;
	}
	else if(mapping == RightAnalogMapping){
		map = (int) table->GetNumber("RightAnalog", 3);
		return map;
	}
	else if(mapping == HalfSpeedToggleMapping){
		map = (int) table->GetNumber("HalfSpeedToggle", 1);
		return map;
	}
	else if(mapping == IntakeInMapping){
		map = (int) table->GetNumber("IntakeInButton", 1);
		return map;
	}
	else if(mapping == IntakeOutMapping){
		map = (int) table->GetNumber("IntakeOutButton", 4);
		return map;
	}
	else if(mapping == FeederMapping){
		map = (int) table->GetNumber("FeederButton", 6);
		return map;
	}
	else if(mapping == ShooterMapping){
		map = (int) table->GetNumber("ShooterButton", 5);
		return map;
	}
	else if(mapping == ShooterIncreaseSpeedMapping){
		map = (int) table->GetNumber("ShooterIncreaseSpeed", 0);
		return map;
	}
	else if(mapping == ShooterDecreaseSpeedMapping){
		map = (int) table->GetNumber("ShooterDecreaseSpeed", 180);
		return map;
	}
	else if(mapping == ClimberMapping){
		map = (int) table->GetNumber("ClimberButton", 3);
		return map;
	}
	return -1;
}
