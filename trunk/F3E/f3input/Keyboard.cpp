
#include "Keyboard.h"

namespace f3
{
	namespace input
	{

		Keyboard::Keyboard( OIS::Keyboard* keyboard ) : _keyboard(keyboard)
		{

		}

		Keyboard::~Keyboard()
		{

		}

		bool Keyboard::isKeyDown( KeyCode code )
		{
			if (_keyboard->isKeyDown( (OIS::KeyCode) code) )
				return true;

			return false;
		}

	}
}
