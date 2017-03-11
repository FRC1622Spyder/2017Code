#include <iostream>
#include <fstream>
#include <memory>
#include <string>

#include <Preferences.h>

#ifndef SRC_CONFIG_H_
#define SRC_CONFIG_H_

class Config{
private:
	enum MOTOR{LeftFront, LeftBack, RightFront, RightBack,
		Intake, Feeder, Shooter, Climber};
	enum MAPPING{LeftAnalog, RightAnalog, HalfSpeedToggle,
		IntakeIn, IntakeOut, Feeder, Shooter, ShooterIncreaseSpeed,
		ShooterDecreaseSpeed, Climber};
public:
	void ConfigInit();
	int GetMotorPort(MOTOR motor);
	int GetControlMapping(MAPPING mapping);
};

#endif
