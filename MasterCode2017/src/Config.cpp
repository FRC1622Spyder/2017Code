#include <iostream>
#include <fstream>
#include <memory>
#include <string>

#include <Preferences.h>
#include <Config.h>

void Config::ConfigInit(){
	std::ifstream configRead;
	std::ofstream configWrite;
	std::string validationString;
	configRead.open("config.properties");
	configWrite.open("config.properties");
	if(std::getline(configRead, validationString) != "##1622-Spyder 2017 Config"){
		configWrite << "##1622-Spyder 2017 Config";
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
	if(motor == LeftFront){
		while(std::getline(configRead, property)){
			if(property.find("Left Front Motor") != std::string::npos){
				port = property[19];
				configRead.close();
				return port;
			}
		}
	}
	else if(motor == LeftBack){
		while(std::getline(configRead, property)){
			if(property.find("Left Back Motor") != std::string::npos){
				port = property[18];
				configRead.close();
				return port;
			}
		}
	}
	else if(motor == RightFront){
		while(std::getline(configRead, property)){
			if(property.find("Right Front Motor") != std::string::npos){
				port = property[20];
				configRead.close();
				return port;
			}
		}
	}
	else if(motor == RightBack){
		while(std::getline(configRead, property)){
			if(property.find("Right Back Motor") != std::string::npos){
				port = property[19];
				configRead.close();
				return port;
			}
		}
	}
	else if(motor == Intake){
		while(std::getline(configRead, property)){
			if(property.find("Intake Motor") != std::string::npos){
				port = property[15];
				configRead.close();
				return port;
			}
		}
	}
	else if(motor == Feeder){
		while(std::getline(configRead, property)){
			if(property.find("Feeder Motor") != std::string::npos){
				port = property[15];
				configRead.close();
				return port;
			}
		}
	}
	else if(motor == Shooter){
		while(std::getline(configRead, property)){
			if(property.find("Shooter Motor") != std::string::npos){
				port = property[16];
				configRead.close();
				return port;
			}
		}
	}
	else if(motor == Climber){
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
	if(mapping == LeftAnalog){
		while(std::getline(configRead, property)){
			if(property.find("Left Analog Stick") != std::string::npos){
				map = property[20];
				configRead.close();
				return map;
			}
		}
	}
	else if(mapping == RightAnalog){
		while(std::getline(configRead, property)){
			if(property.find("Right Analog Stick") != std::string::npos){
				map = property[21];
				configRead.close();
				return map;
			}
		}
	}
	else if(mapping == HalfSpeedToggle){
		while(std::getline(configRead, property)){
			if(property.find("Half Speed Toggle") != std::string::npos){
				map = property[20];
				configRead.close();
				return map;
			}
		}
	}
	else if(mapping == IntakeIn){
		while(std::getline(configRead, property)){
			if(property.find("Intake In Button") != std::string::npos){
				map = property[19];
				configRead.close();
				return map;
			}
		}
	}
	else if(mapping == IntakeOut){
		while(std::getline(configRead, property)){
			if(property.find("Intake Out Button") != std::string::npos){
				map= property[20];
				configRead.close();
				return map;
			}
		}
	}
	else if(mapping == Feeder){
		while(std::getline(configRead, property)){
			if(property.find("Feeder Button") != std::string::npos){
				map = property[16];
				configRead.close();
				return map;
			}
		}
	}
	else if(mapping == Shooter){
		while(std::getline(configRead, property)){
			if(property.find("Shooter Toggle") != std::string::npos){
				map = property[17];
				configRead.close();
				return map;
			}
		}
	}
	else if(mapping == ShooterIncreaseSpeed){
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
	else if(mapping == ShooterDecreaseSpeed){
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
	else if(mapping == Climber){
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
