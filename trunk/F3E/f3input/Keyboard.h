#ifndef Keyboard_h__
#define Keyboard_h__

#include "Device.h"
#include "OISKeyboard.h"
#include "KeyCode.h"

#include <f3base/Common.h>

namespace f3
{
	namespace input
	{
		class Keyboard : public Device
		{
			OIS::Keyboard* _keyboard;

		public:
			Keyboard(OIS::Keyboard* keyboard);
			virtual ~Keyboard();

			bool Keyboard::isKeyDown( KeyCode code );
		};


	}
}
#endif // Keyboard_h__
