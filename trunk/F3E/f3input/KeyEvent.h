#ifndef KeyEvent_h__
#define KeyEvent_h__


#include "Device.h"
#include "KeyCode.h"

namespace f3
{
	namespace input 
	{

		class KeyEvent
		{
		public:
			Device* device;
			KeyCode key;

		};
	}
}
#endif // KeyEvent_h__
