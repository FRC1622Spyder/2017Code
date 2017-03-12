#include <iostream>
#include <fstream>
#include <memory>
#include <string>

#include <Config.h>

void Config::ConfigInit(){
	std::ifstream configRead;
	std::ofstream configWrite;
	std::string validationString;
	configRead.open("config.properties");
	configWrite.open("config.properties");
	if(std::getline(configRead, validationString) != "##1622-SPYDER CONFIG 2017"){
		configWrite << "##1622-SPYDER CONFIG 2017";
		configWrite << '\n' << "##DO NOT EDIT THIS HEADER";
		configWrite << '\n' << "##ALWAYS FORMAT ENTRIES WITH THE DEFAULT SPACING";
		configWrite << '\n' << "##LIKE THIS: Sample Motor = 9";

		configWrite << '\n' << '\n' << "##Motor Ports";
		configWrite << '\n' << "Left Front Motor = 3";
		configWrite << '\n' << "Left Back Motor = 4";
		configWrite << '\n' << "Right Front Motor = 1";
		configWrite << '\n' << "Right Back Motor = 2";
		configWrite << '\n' << "Intake Motor = 6";
		configWrite << '\n' << "Feeder Motor = 5";
		configWrite << '\n' << "Shooter Motor = 8";
		configWrite << '\n' << "Climber Motor = 7";

		configWrite << '\n' << '\n' << "##Control Mapping:";
		configWrite << '\n' << "Left Analog Stick = 1";
		configWrite << '\n' << "Right Analog Stick = 3";
		configWrite << '\n' << "Half Speed Toggle = 1";
		configWrite << '\n' << "Intake In Button = 1";
		configWrite << '\n' << "Intake Out Button = 4";
		configWrite << '\n' << "Feeder Button = 6";
		configWrite << '\n' << "Shooter Toggle = 5";
		configWrite << '\n' << "Shooter Increase Speed POV = 0";
		configWrite << '\n' << "Shooter Decrease Speed POV = 180";
		configWrite << '\n' << "Climber Button = 3";
	}
	configRead.close();
	configWrite.close();
}

int Config::GetMotorPort(Config::MOTOR motor){
	std::ifstream configRead;
	configRead.open("config.properties");
	std::string property;
	int port;
	if(motor == LeftFrontMotor){
		while(std::getline(configRead, property)){
			if(property.find("Left Front Motor") != std::string::npos){
				port = property[19];
				configRead.close();
				return port;
			}
		}
	}
	else if(motor == LeftBackMotor){
		while(std::getline(configRead, property)){
			if(property.find("Left Back Motor") != std::string::npos){
				port = property[18];
				configRead.close();
				return port;
			}
		}
	}
	else if(motor == RightFrontMotor){
		while(std::getline(configRead, property)){
			if(property.find("Right Front Motor") != std::string::npos){
				port = property[20];
				configRead.close();
				return port;
			}
		}
	}
	else if(motor == RightBackMotor){
		while(std::getline(configRead, property)){
			if(property.find("Right Back Motor") != std::string::npos){
				port = property[19];
				configRead.close();
				return port;
			}
		}
	}
	else if(motor == IntakeMotor){
		while(std::getline(configRead, property)){
			if(property.find("Intake Motor") != std::string::npos){
				port = property[15];
				configRead.close();
				return port;
			}
		}
	}
	else if(motor == FeederMotor){
		while(std::getline(configRead, property)){
			if(property.find("Feeder Motor") != std::string::npos){
				port = property[15];
				configRead.close();
				return port;
			}
		}
	}
	else if(motor == ShooterMotor){
		while(std::getline(configRead, property)){
			if(property.find("Shooter Motor") != std::string::npos){
				port = property[16];
				configRead.close();
				return port;
			}
		}
	}
	else if(motor == ClimberMotor){
		while(std::getline(configRead, property)){
			if(property.find("Climber Motor") != std::string::npos){
				port = property[16];
				configRead.close();
				return port;
			}
		}
	}
	return -1;
}

int Config::GetControlMapping(MAPPING mapping){
	std::ifstream configRead;
	configRead.open("config.properties");
	std::string property;
	int map;
	if(mapping == LeftAnalogMapping){
		while(std::getline(configRead, property)){
			if(property.find("Left Analog Stick") != std::string::npos){
				map = property[20];
				configRead.close();
				return map;
			}
		}
	}
	else if(mapping == RightAnalogMapping){
		while(std::getline(configRead, property)){
			if(property.find("Right Analog Stick") != std::string::npos){
				map = property[21];
				configRead.close();
				return map;
			}
		}
	}
	else if(mapping == HalfSpeedToggleMapping){
		while(std::getline(configRead, property)){
			if(property.find("Half Speed Toggle") != std::string::npos){
				map = property[20];
				configRead.close();
				return map;
			}
		}
	}
	else if(mapping == IntakeInMapping){
		while(std::getline(configRead, property)){
			if(property.find("Intake In Button") != std::string::npos){
				map = property[19];
				configRead.close();
				return map;
			}
		}
	}
	else if(mapping == IntakeOutMapping){
		while(std::getline(configRead, property)){
			if(property.find("Intake Out Button") != std::string::npos){
				map= property[20];
				configRead.close();
				return map;
			}
		}
	}
	else if(mapping == FeederMapping){
		while(std::getline(configRead, property)){
			if(property.find("Feeder Button") != std::string::npos){
				map = property[16];
				configRead.close();
				return map;
			}
		}
	}
	else if(mapping == ShooterMapping){
		while(std::getline(configRead, property)){
			if(property.find("Shooter Toggle") != std::string::npos){
				map = property[17];
				configRead.close();
				return map;
			}
		}
	}
	else if(mapping == ShooterIncreaseSpeedMapping){
		while(std::getline(configRead, property)){
			if(property.find("Shooter Increase Speed POV") != std::string::npos){
				if(property.length() == 30){
					map = property[29];
				}
				else if(property.length() == 31){
					int ones = property[30];
					int tens = property[29];
					map = tens + ones;
				}
				else if(property.length() == 32){
					int ones = property[31];
					int tens = property[30];
					int hundreds = property[29];
					map = hundreds + tens + ones;
				}
				else {
					configRead.close();
					return -1;
				}
				configRead.close();
				return map;
			}
		}
	}
	else if(mapping == ShooterDecreaseSpeedMapping){
		while(std::getline(configRead, property)){
			if(property.find("Shooter Decrease Speed POV") != std::string::npos){
				if(property.length() == 30){
					map = property[29];
				}
				else if(property.length() == 31){
					int ones = property[30];
					int tens = property[29];
					map = tens + ones;
				}
				else if(property.length() == 32){
					int ones = property[31];
					int tens = property[30];
					int hundreds = property[29];
					map = hundreds + tens + ones;
				}
				else {
					configRead.close();
					return -1;
				}
				configRead.close();
				return map;
			}
		}
	}
	else if(mapping == ClimberMapping){
		while(std::getline(configRead, property)){
			if(property.find("Climber Button") != std::string::npos){
				map = property[17];
				configRead.close();
				return map;
			}
		}
	}
	return -1;
}
