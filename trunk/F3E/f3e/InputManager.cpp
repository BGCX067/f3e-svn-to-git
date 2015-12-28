#include "InputManager.h"

#include <iostream>
#include <vector>
#include <sstream>
#include <iostream>
#include <algorithm>
#include "Common.h"
#include "InputEventHandler.h"

namespace f3
{
	namespace input
	{
		InputEventHandler handler;

		InputManager::InputManager(void)
		{
		}


		InputManager::~InputManager(void)
		{
		}

		void InputManager::init()
		{
			OIS::ParamList pl;

			HWND hWnd = f3::plattform::hWnd;

			std::ostringstream wnd;
			wnd << (size_t)hWnd;

			pl.insert(std::make_pair( std::string("WINDOW"), wnd.str() ));

			//Default mode is foreground exclusive..but, we want to show mouse - so nonexclusive
			pl.insert(std::make_pair(std::string("w32_mouse"), std::string("DISCL_FOREGROUND" )));
			pl.insert(std::make_pair(std::string("w32_mouse"), std::string("DISCL_NONEXCLUSIVE")));


			//This never returns null.. it will raise an exception on errors
			inputManager = OIS::InputManager::createInputSystem(pl);

			//Lets enable all addons that were compiled in:
			inputManager->enableAddOnFactory(OIS::InputManager::AddOn_All);

			//Print debugging information
			unsigned int v = inputManager->getVersionNumber();
			std::cout << "OIS Version: " << (v>>16 ) << "." << ((v>>8) & 0x000000FF) << "." << (v & 0x000000FF)
				<< "\nRelease Name: " << inputManager->getVersionName()
				<< "\nManager: " << inputManager->inputSystemName()
				<< "\nTotal Keyboards: " << inputManager->getNumberOfDevices(OIS::OISKeyboard)
				<< "\nTotal Mice: " << inputManager->getNumberOfDevices(OIS::OISMouse)
				<< "\nTotal JoySticks: " << inputManager->getNumberOfDevices(OIS::OISJoyStick);

			//List all devices
			OIS::DeviceList list = inputManager->listFreeDevices();
			const char *deviceType[6] = {"OISUnknown", "OISKeyboard", "OISMouse", "OISJoyStick", "OISTablet", "OISOther"};

			for( OIS::DeviceList::iterator i = list.begin(); i != list.end(); ++i )
				std::cout << "\n\tDevice: " << deviceType[i->first] << " Vendor: " << i->second;

			keyboard = (OIS::Keyboard*)inputManager->createInputObject( OIS::OISKeyboard, true );
			keyboard->setEventCallback( &handler );

			mouse = (OIS::Mouse*)inputManager->createInputObject( OIS::OISMouse, true );
			mouse->setEventCallback( &handler );
			const OIS::MouseState &ms = mouse->getMouseState();
			ms.width = 100;
			ms.height = 100;

			try
			{
				//This demo uses at most 4 joysticks - use old way to create (i.e. disregard vendor)
				int numSticks = std::min<int>(inputManager->getNumberOfDevices(OIS::OISJoyStick), 4);
				for( int i = 0; i < numSticks; ++i )
				{
					joystick[i] = (OIS::JoyStick*)inputManager->createInputObject( OIS::OISJoyStick, true );
					joystick[i]->setEventCallback( &handler );
					std::cout << "\n\nCreating Joystick " << (i + 1)
						<< "\n\tAxes: " << joystick[i]->getNumberOfComponents(OIS::OIS_Axis)
						<< "\n\tSliders: " << joystick[i]->getNumberOfComponents(OIS::OIS_Slider)
						<< "\n\tPOV/HATs: " << joystick[i]->getNumberOfComponents(OIS::OIS_POV)
						<< "\n\tButtons: " << joystick[i]->getNumberOfComponents(OIS::OIS_Button)
						<< "\n\tVector3: " << joystick[i]->getNumberOfComponents(OIS::OIS_Vector3);
				}
			}
			catch(OIS::Exception &ex)
			{
				std::cout << "\nException raised on joystick creation: " << ex.eText << std::endl;
			}
		}

		void InputManager::update()
		{
			if( keyboard )
			{
				keyboard->capture();
				//if( !g_kb->buffered() )
				//	handleNonBufferedKeys();
			}

			if( mouse )
			{
				mouse->capture();
				//if( !g_m->buffered() )
				//	handleNonBufferedMouse();
			}

			for( int i = 0; i < 4 ; ++i )
			{
				if( joystick[i] )
				{
					joystick[i]->capture();
					/*if( !joystick[i]->buffered() )
						handleNonBufferedJoy( joystick[i] );*/
				}
			}
		}

	}
}