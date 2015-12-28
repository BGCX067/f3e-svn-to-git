#include "KeyboardSpaceShipController.h"
#include <f3base/Common.h>
#include <f3input/Manager.h>
#include <f3e/Main.h>
#include <f3input/Keyboard.h>

KeyboardSpaceShipController::KeyboardSpaceShipController(SpaceShip* ship, f3i::Keyboard* keyboard ) : _ship(ship), _keyboard(keyboard)
{

}


KeyboardSpaceShipController::~KeyboardSpaceShipController(void)
{
}


bool KeyboardSpaceShipController::keyPressed( const f3::input::KeyEvent &arg )
{
	//if ( arg.key == f3i::KC_W )
	//	ship->throttle(10.0f);

	//if ( arg.key == f3::input::KC_A )
	//	ship->steer(0.0015f);

	//if ( arg.key == f3::input::KC_D )
	//	ship->steer(-0.0015f);

	return true;
}

bool KeyboardSpaceShipController::keyReleased( const f3::input::KeyEvent &arg )
{

	//if ( arg.key == f3i::KC_W )
	//	ship->throttle(0.0f);

	//if ( arg.key == f3::input::KC_A || arg.key == f3::input::KC_D )
	//	ship->steer(0.0f);

	//if ( f3::input::manager.isKeyDown(f3::input::KC_A) )
	//	ship->steer(0.0015f);
	//else if ( f3::input::manager.isKeyDown(f3::input::KC_D) )
	//	ship->steer(-0.0015f);
	//else
	//	ship->steer(0.0f);

	return true;
}

void KeyboardSpaceShipController::update()
{	
	if ( _keyboard->isKeyDown(f3i::KC_W) )
		_ship->throttle(100.0f);
	else if ( _keyboard->isKeyDown(f3i::KC_S) )
		_ship->throttle(-60.0f);
	else
		_ship->throttle(0.0f);

	if ( _keyboard->isKeyDown(f3i::KC_Q) )
		_ship->strafe(-10.0f);
	else if (  _keyboard->isKeyDown(f3i::KC_E) )
		_ship->strafe(10.0f);
	else
		_ship->strafe(0.0f);

	if (  _keyboard->isKeyDown(f3::input::KC_A) )
		_ship->steer(0.0015f);
	else if (  _keyboard->isKeyDown(f3::input::KC_D) )
		_ship->steer(-0.0015f);
	else
		_ship->steer(0.0f);

	if (  _keyboard->isKeyDown(f3::input::KC_SPACE) )
		_ship->fire();
}
