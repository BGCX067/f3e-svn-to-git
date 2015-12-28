#include "EventHandler.h"
#include "KeyEvent.h"
#include <algorithm>

namespace f3
{
	namespace input
	{

		EventHandler::EventHandler(void)
		{
		}


		EventHandler::~EventHandler(void)
		{
		}

		bool EventHandler::keyPressed( const OIS::KeyEvent &arg ) 
		{
			//std::cout << " KeyPressed {" << arg.key
			//	<< ", " << ((OIS::Keyboard*)(arg.device))->getAsString(arg.key)
			//	<< "} || Character (" << (char)arg.text << ")" << std::endl;

			f3::input::KeyEvent keyevent;

			keyevent.key = (f3::input::KeyCode) arg.key;

			for(std::vector<IKeyListener*>::iterator it = keylistener.begin(); it != keylistener.end(); ++it)
			{
				(*it)->keyPressed(keyevent);
			}

			return true;
		}

		bool EventHandler::keyReleased( const OIS::KeyEvent &arg ) 
		{
			f3::input::KeyEvent keyevent;
			
			keyevent.key = (f3::input::KeyCode) arg.key;

			for(std::vector<IKeyListener*>::iterator it = keylistener.begin(); it != keylistener.end(); ++it)
			{
				(*it)->keyReleased(keyevent);
			}

			/*if( arg.key == KC_ESCAPE || arg.key == KC_Q )
			appRunning = false;*/
			return true;
		}

		bool EventHandler::mouseMoved( const OIS::MouseEvent &arg ) 
		{
			const OIS::MouseState& s = arg.state;
			std::cout << "\nMouseMoved: Abs("
				<< s.X.abs << ", " << s.Y.abs << ", " << s.Z.abs << ") Rel("
				<< s.X.rel << ", " << s.Y.rel << ", " << s.Z.rel << ")";
			return true;
		}

		bool EventHandler::mousePressed( const OIS::MouseEvent &arg, OIS::MouseButtonID id )
		{
			const OIS::MouseState& s = arg.state;
			std::cout << "\nMouse button #" << id << " pressed. Abs("
				<< s.X.abs << ", " << s.Y.abs << ", " << s.Z.abs << ") Rel("
				<< s.X.rel << ", " << s.Y.rel << ", " << s.Z.rel << ")";
			return true;
		}

		bool EventHandler::mouseReleased( const OIS::MouseEvent &arg, OIS::MouseButtonID id ) 
		{
			const OIS::MouseState& s = arg.state;
			std::cout << "\nMouse button #" << id << " released. Abs("
				<< s.X.abs << ", " << s.Y.abs << ", " << s.Z.abs << ") Rel("
				<< s.X.rel << ", " << s.Y.rel << ", " << s.Z.rel << ")";
			return true;
		}

		bool EventHandler::buttonPressed( const OIS::JoyStickEvent &arg, int button ) 
		{
			std::cout << std::endl << arg.device->vendor() << ". Button Pressed # " << button;
			return true;
		}

		bool EventHandler::buttonReleased( const OIS::JoyStickEvent &arg, int button ) 
		{
			std::cout << std::endl << arg.device->vendor() << ". Button Released # " << button;
			return true;
		}

		bool EventHandler::axisMoved( const OIS::JoyStickEvent &arg, int axis )
		{
			//Provide a little dead zone
			if( arg.state.mAxes[axis].abs > 2500 || arg.state.mAxes[axis].abs < -2500 )
				std::cout << std::endl << arg.device->vendor() << ". Axis # " << axis << " Value: " << arg.state.mAxes[axis].abs;
			return true;
		}

		bool EventHandler::povMoved( const OIS::JoyStickEvent &arg, int pov )
		{
			std::cout << std::endl << arg.device->vendor() << ". POV" << pov << " ";

			if( arg.state.mPOV[pov].direction & OIS::Pov::North ) //Going up
				std::cout << "North";
			else if( arg.state.mPOV[pov].direction & OIS::Pov::South ) //Going down
				std::cout << "South";

			if( arg.state.mPOV[pov].direction & OIS::Pov::East ) //Going right
				std::cout << "East";
			else if( arg.state.mPOV[pov].direction & OIS::Pov::West ) //Going left
				std::cout << "West";

			if( arg.state.mPOV[pov].direction == OIS::Pov::Centered ) //stopped/centered out
				std::cout << "Centered";
			return true;
		}

		bool EventHandler::vector3Moved( const OIS::JoyStickEvent &arg, int index)
		{
			std::cout.precision(2);
			std::cout.flags(std::ios::fixed | std::ios::right);
			std::cout << std::endl << arg.device->vendor() << ". Orientation # " << index 
				<< " X Value: " << arg.state.mVectors[index].x
				<< " Y Value: " << arg.state.mVectors[index].y
				<< " Z Value: " << arg.state.mVectors[index].z;
			std::cout.precision();
			std::cout.flags();
			return true;
		}

		void EventHandler::removeListener( IKeyListener* listener )
		{
			keylistener.erase(std::remove(keylistener.begin(), keylistener.end(), listener), keylistener.end());
		}

		void EventHandler::registerListener(IKeyListener* listener)
		{
			keylistener.insert(keylistener.begin(), listener);
		}
	}
}