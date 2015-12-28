#ifndef Joystick_h__
#define Joystick_h__

#include <f3base/Common.h>

#include "Device.h"
#include "OISJoystick.h"
#include "KeyCode.h"

namespace f3
{
	namespace input
	{
		class Joystick : public Device
		{

			OIS::JoyStick* _joystick;

		public:
			Joystick(OIS::JoyStick* joystick);
			~Joystick(void);
			bool isButtonDown(f3::UI32 button);
			f3::I32 Joystick::getAxesValue(f3::UI32 axes);
		};

	}
}
#endif // Joystick_h__
