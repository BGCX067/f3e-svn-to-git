#include "InputEventHandler.h"

namespace f3
{
	namespace input
	{

		InputEventHandler::InputEventHandler(void)
		{
		}


		InputEventHandler::~InputEventHandler(void)
		{
		}

		bool InputEventHandler::keyPressed( const OIS::KeyEvent &arg ) 
		{
			std::cout << " KeyPressed {" << arg.key
				<< ", " << ((OIS::Keyboard*)(arg.device))->getAsString(arg.key)
				<< "} || Character (" << (char)arg.text << ")" << std::endl;
			return true;
		}

		bool InputEventHandler::keyReleased( const OIS::KeyEvent &arg ) 
		{
			/*if( arg.key == KC_ESCAPE || arg.key == KC_Q )
			appRunning = false;*/
			return true;
		}

		bool InputEventHandler::mouseMoved( const OIS::MouseEvent &arg ) 
		{
			const OIS::MouseState& s = arg.state;
			std::cout << "\nMouseMoved: Abs("
				<< s.X.abs << ", " << s.Y.abs << ", " << s.Z.abs << ") Rel("
				<< s.X.rel << ", " << s.Y.rel << ", " << s.Z.rel << ")";
			return true;
		}

		bool InputEventHandler::mousePressed( const OIS::MouseEvent &arg, OIS::MouseButtonID id )
		{
			const OIS::MouseState& s = arg.state;
			std::cout << "\nMouse button #" << id << " pressed. Abs("
				<< s.X.abs << ", " << s.Y.abs << ", " << s.Z.abs << ") Rel("
				<< s.X.rel << ", " << s.Y.rel << ", " << s.Z.rel << ")";
			return true;
		}

		bool InputEventHandler::mouseReleased( const OIS::MouseEvent &arg, OIS::MouseButtonID id ) 
		{
			const OIS::MouseState& s = arg.state;
			std::cout << "\nMouse button #" << id << " released. Abs("
				<< s.X.abs << ", " << s.Y.abs << ", " << s.Z.abs << ") Rel("
				<< s.X.rel << ", " << s.Y.rel << ", " << s.Z.rel << ")";
			return true;
		}

		bool InputEventHandler::buttonPressed( const OIS::JoyStickEvent &arg, int button ) 
		{
			std::cout << std::endl << arg.device->vendor() << ". Button Pressed # " << button;
			return true;
		}

		bool InputEventHandler::buttonReleased( const OIS::JoyStickEvent &arg, int button ) 
		{
			std::cout << std::endl << arg.device->vendor() << ". Button Released # " << button;
			return true;
		}

		bool InputEventHandler::axisMoved( const OIS::JoyStickEvent &arg, int axis )
		{
			//Provide a little dead zone
			if( arg.state.mAxes[axis].abs > 2500 || arg.state.mAxes[axis].abs < -2500 )
				std::cout << std::endl << arg.device->vendor() << ". Axis # " << axis << " Value: " << arg.state.mAxes[axis].abs;
			return true;
		}

		bool InputEventHandler::povMoved( const OIS::JoyStickEvent &arg, int pov )
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

		bool InputEventHandler::vector3Moved( const OIS::JoyStickEvent &arg, int index)
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
	}
}