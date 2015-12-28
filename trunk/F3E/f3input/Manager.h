#ifndef InputManager_h__
#define InputManager_h__

#include <f3base/Common.h>


#include <iostream>
#include <vector>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <Windows.h>

#include "IKeyListener.h"
#include "KeyCode.h"

namespace OIS
{
	class InputManager;
	class Keyboard;
	class Mouse;
	class JoyStick;
};

namespace f3
{
	namespace input
	{
		class EventHandler;
		class Device;
		class MouseState;

		class DLL Manager
		{
			EventHandler* handler;

			OIS::InputManager *inputManager;	//Our Input System
			OIS::Keyboard *_keyboard;				//Keyboard Device
			OIS::Mouse	 *mouse;				//Mouse Device
			OIS::JoyStick* joystick[4];	//This demo supports up to 4 controllers


		public:
			std::vector<Device*> _devices;
			Manager(void);
			~Manager(void);
			void init();
			void shutdown();
			void update();
			bool isKeyDown(KeyCode key);
			void registerListener(IKeyListener* listener);
			void removeListener(IKeyListener* listener);
			MouseState getMouseState();
		};

	}
}
#endif // InputManager_h__
