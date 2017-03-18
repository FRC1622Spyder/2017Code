#include <iostream>
#include <fstream>
#include <memory>
#include <string>

#include <NetworkTables/NetworkTable.h>

#ifndef SRC_CONFIG_H_
#define SRC_CONFIG_H_

class Config{
public:
	std::shared_ptr<NetworkTable> table;
	enum MOTOR{LeftFrontMotor, LeftBackMotor, RightFrontMotor, RightBackMotor,
		IntakeMotor, FeederMotor, ShooterMotor, ClimberMotor};
	enum MAPPING{LeftAnalogMapping, RightAnalogMapping, HalfSpeedToggleMapping,
		AutomaticDriveMapping, IntakeInMapping, IntakeOutMapping, FeederMapping, ShooterMapping,
		ShooterIncreaseSpeedMapping, ShooterDecreaseSpeedMapping, ClimberMapping};
	void ConfigInit();
	int GetMotorPort(MOTOR motor);
	int GetControlMapping(MAPPING mapping);
};

#endif
