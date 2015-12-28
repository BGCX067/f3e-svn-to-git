#ifndef InputManager_h__
#define InputManager_h__


#include "OISInputManager.h"
#include "OISException.h"
#include "OISKeyboard.h"
#include "OISMouse.h"
#include "OISJoyStick.h"
#include "OISEvents.h"

#include "Common.h"

namespace f3
{
	namespace input
	{

		class DLL InputManager
		{
			

		public:
			InputManager(void);
			~InputManager(void);
			void init();
			void shutdown();
			void update();

			OIS::InputManager *inputManager;	//Our Input System
			OIS::Keyboard *keyboard;				//Keyboard Device
			OIS::Mouse	 *mouse;				//Mouse Device
			OIS::JoyStick* joystick[4];	//This demo supports up to 4 controllers
		};

	}
}
#endif // InputManager_h__
