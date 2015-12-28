#ifndef SpaceShipController_h__
#define SpaceShipController_h__

#include <f3input/IKeyListener.h>
#include <f3input/KeyEvent.h>
#include <f3input/Keyboard.h>

#include "SpaceShip.h"

class KeyboardSpaceShipController : public f3::input::IKeyListener
{
	SpaceShip* _ship;
	f3i::Keyboard* _keyboard;

public:
	KeyboardSpaceShipController(SpaceShip* ship, f3i::Keyboard* keyboard);
	KeyboardSpaceShipController::~KeyboardSpaceShipController(void);

	bool keyPressed( const f3::input::KeyEvent &arg );
	bool keyReleased( const f3::input::KeyEvent &arg );
	void update();
};
#endif // SpaceShipController_h__