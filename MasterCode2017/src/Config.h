#include <iostream>
#include <fstream>
#include <memory>
#include <string>

#include <Preferences.h>

#ifndef SRC_CONFIG_H_
#define SRC_CONFIG_H_

class Config{
private:
	int motors[9];
	int controls[9];

public:
	void ConfigInit();
	int GetMotorPort(std::string motor);
	int GetControlMapping(std::string control);
};

#endif
