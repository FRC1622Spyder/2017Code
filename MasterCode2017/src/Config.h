#include <iostream>
#include <fstream>
#include <memory>
#include <string>

#include <Preferences.h>

#ifndef SRC_CONFIG_H_
#define SRC_CONFIG_H_

class Config{
public:
	enum MOTOR{LeftFrontMotor, LeftBackMotor, RightFrontMotor, RightBackMotor,
		IntakeMotor, FeederMotor, ShooterMotor, ClimberMotor};
	enum MAPPING{LeftAnalogMapping, RightAnalogMapping, HalfSpeedToggleMapping,
		IntakeInMapping, IntakeOutMapping, FeederMapping, ShooterMapping,
		ShooterIncreaseSpeedMapping, ShooterDecreaseSpeedMapping, ClimberMapping};
	void ConfigInit();
	int GetMotorPort(MOTOR motor);
	int GetControlMapping(MAPPING mapping);
};

#endif
