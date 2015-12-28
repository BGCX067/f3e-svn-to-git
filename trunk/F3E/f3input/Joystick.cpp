#include "Joystick.h"

namespace f3
{
	namespace input
	{
		Joystick::Joystick( OIS::JoyStick* joystick ) : _joystick(joystick)
		{
		}


		Joystick::~Joystick(void)
		{
		}

		bool Joystick::isButtonDown( f3::UI32 button )
		{
			OIS::JoyStickState jss = _joystick->getJoyStickState();
			
			if (jss.mButtons.size() < button)
				return false;

			if (jss.mButtons[button])
				return true;

			return false;
		}

		f3::I32  Joystick::getAxesValue(f3::UI32 axes)
		{
			OIS::JoyStickState jss = _joystick->getJoyStickState();

			if (jss.mAxes.size() < axes)
				return 0;

			return jss.mAxes[axes].abs;
		}
	}

}