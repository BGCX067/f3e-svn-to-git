#ifndef IJoystickListener_h__
#define IJoystickListener_h__


#include <f3base/Common.h>
#include "KeyEvent.h"

namespace f3
{
	namespace input 
	{

		class DLL IJoystickListener
		{
		public:
			virtual bool buttonPressed( const KeyEvent &arg ) = 0;
			virtual bool buttonReleased( const KeyEvent &arg ) = 0;
		};
	}
}

#endif // IJoystickListener_h__
