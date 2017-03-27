#ifndef SRC_FLASHLIGHT_H_
#define SRC_FLASHLIGHT_H_
#include <Relay.h>
#include <Joystick.h>
#include <IterativeRobot.h>
class Flashlight{
private:
	Relay *flashlightRelay;
	Joystick *drivestick;
	bool isLit;
	bool toggleOn;
public:
	void FlashlightInit();
	void FlashlightTeleopPeriodic();
};
#endif /* SRC_FLASHLIGHT_H_ */
