#ifndef JoystickSpaceShipController_h__
#define JoystickSpaceShipController_h__



#include <f3input/IKeyListener.h>
#include <f3input/KeyEvent.h>
#include <f3input/Joystick.h>

#include "SpaceShip.h"

class JoystickSpaceShipController
{
	SpaceShip* _ship;
	f3i::Joystick* _joystick;

public:
	JoystickSpaceShipController(SpaceShip* ship, f3i::Joystick* joystick);
	JoystickSpaceShipController::~JoystickSpaceShipController(void);

	void update();
};
#endif // JoystickSpaceShipController_h__