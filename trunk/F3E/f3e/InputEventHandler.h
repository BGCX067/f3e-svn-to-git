#pragma once

#include "OISInputManager.h"
#include "OISException.h"
#include "OISKeyboard.h"
#include "OISMouse.h"
#include "OISJoyStick.h"
#include "OISEvents.h"


#include <iostream>
#include <vector>
#include <sstream>
//////////// Common Event handler class ////////

namespace f3
{
	namespace input
	{

class InputEventHandler : public OIS::KeyListener, public OIS::MouseListener, public OIS::JoyStickListener
{
public:
	InputEventHandler();
	~InputEventHandler();
	bool keyPressed( const OIS::KeyEvent &arg );
	bool keyReleased( const OIS::KeyEvent &arg );
	bool mouseMoved( const OIS::MouseEvent &arg );
	bool mousePressed( const OIS::MouseEvent &arg, OIS::MouseButtonID id );
	bool mouseReleased( const OIS::MouseEvent &arg, OIS::MouseButtonID id );
	bool buttonPressed( const OIS::JoyStickEvent &arg, int button );
	bool buttonReleased( const OIS::JoyStickEvent &arg, int button );
	bool axisMoved( const OIS::JoyStickEvent &arg, int axis );
	bool povMoved( const OIS::JoyStickEvent &arg, int pov );
	bool vector3Moved( const OIS::JoyStickEvent &arg, int index);
};

	}
}