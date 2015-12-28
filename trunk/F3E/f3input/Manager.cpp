#include "Manager.h"

#include <f3base/Common.h>
#include <f3input/Keyboard.h>
#include <f3input/Joystick.h>
#include <f3input/EventHandler.h>

#include <OISInputManager.h>
#include "OISException.h"
#include "OISKeyboard.h"
#include "OISMouse.h"
#include "OISJoyStick.h"
#include "OISEvents.h"
#include "MouseState.h"

namespace f3
{
	namespace input
	{

		Manager::Manager(void)
		{
		}


		Manager::~Manager(void)
		{
		}

		void Manager::init()
		{
			handler = new EventHandler();

			OIS::ParamList pl;

			HWND hWnd = f3::platform::hWnd;

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

			f3u::log << f3u::info << "Starting Input Manager (OIS Version: " << (v>>16 ) << "." << ((v>>8) & 0x000000FF) << "." << (v & 0x000000FF) << ", " << 
				"Release Name: " << inputManager->getVersionName() << ")" << f3u::endl;
			f3u::log << f3u::info << "Total Keyboards: " << inputManager->getNumberOfDevices(OIS::OISKeyboard) << f3u::endl;
			f3u::log << f3u::info << "Total Mice: " << inputManager->getNumberOfDevices(OIS::OISMouse) << f3u::endl;
			f3u::log << f3u::info << "Total JoySticks: " << inputManager->getNumberOfDevices(OIS::OISJoyStick) << f3u::endl;

			//List all devices
			OIS::DeviceList list = inputManager->listFreeDevices();
			const char *deviceType[6] = {"OISUnknown", "OISKeyboard", "OISMouse", "OISJoyStick", "OISTablet", "OISOther"};

			for( OIS::DeviceList::iterator i = list.begin(); i != list.end(); ++i )
				f3u::log << f3u::info << "Device: " << deviceType[i->first] << " Vendor: " << i->second << f3u::endl;

			// CREATE KEYBOARD
			_keyboard = (OIS::Keyboard*)inputManager->createInputObject( OIS::OISKeyboard, true );
			_keyboard->setEventCallback( handler );

			_devices.insert(_devices.begin(), new f3i::Keyboard(_keyboard));

			// CREATE MOUSE
			mouse = (OIS::Mouse*)inputManager->createInputObject( OIS::OISMouse, true );
			//mouse->setEventCallback( &handler );
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

					if (i == 0)
						_devices.insert(_devices.end(), new f3i::Joystick(joystick[i]));


					joystick[i]->setEventCallback( handler );
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

		void Manager::update()
		{
			if( _keyboard )
			{
				_keyboard->capture();
				/*if( !keyboard->buffered() )
					handler.keyPressed(keyboard->copyKeyStates();*/
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

		MouseState Manager::getMouseState()
		{
			const OIS::MouseState& s = mouse->getMouseState();
			f3i::MouseState ms;
			ms._x = s.X.abs;
			ms._y = s.Y.abs;
			ms._z = s.Z.abs;
			ms._relX = s.X.rel;
			ms._relY = s.Y.rel;
			ms._relZ = s.Z.rel;
			return ms;
		}

		void Manager::registerListener(IKeyListener* listener)
		{
			handler->registerListener(listener);
		}

		void Manager::removeListener( IKeyListener* listener )
		{
			handler->removeListener(listener);
		}

		bool Manager::isKeyDown( KeyCode key )
		{
			return _keyboard->isKeyDown((OIS::KeyCode) key);
		}


	}
}