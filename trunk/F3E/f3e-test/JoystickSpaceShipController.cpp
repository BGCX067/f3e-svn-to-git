#include "JoystickSpaceShipController.h"
#include <f3base/Common.h>
#include <f3input/Manager.h>
#include <f3e/Main.h>

JoystickSpaceShipController::JoystickSpaceShipController(SpaceShip* ship, f3i::Joystick* joystick ) : _ship(ship), _joystick(joystick)
{

}


JoystickSpaceShipController::~JoystickSpaceShipController(void)
{
}


void JoystickSpaceShipController::update()
{
	if ( _joystick->isButtonDown(0) )
		_ship->throttle(100.0f);
	else
		_ship->throttle(0.0f);
/*
	if ( _keyboard->isKeyDown(f3i::KC_Q) )
		_ship->strafe(-10.0f);
	else if (  _keyboard->isKeyDown(f3i::KC_E) )
		_ship->strafe(10.0f);
	else
		_ship->strafe(0.0f);
*/
	f3::I32 val = _joystick->getAxesValue(1);

	f3::F32 f = val / 20000.0f;
	f3::I32 deadzone = 1500;

	if (val < -deadzone)
		_ship->steer(-0.0015f*f);
	if (val > deadzone)
		_ship->steer(-0.0015f*f);
	if (val < deadzone && val > -deadzone)
		_ship->steer(0.0f);

}
