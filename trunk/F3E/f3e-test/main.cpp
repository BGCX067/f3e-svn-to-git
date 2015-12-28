#include <f3base/Common.h>
#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
#include <iterator>

#include "main.h"

#include <f3e/Main.h>
#include <f3scene/Node.h>
#include <f3scene/MeshNode.h>
#include <f3scene/Graph.h>
#include <f3graphics/QuadMesh.h>
#include <f3scene/TextNode.h>
#include <f3math/Vector.h>
#include <f3e/Animator.h>
#include <f3e/MoveAnimation.h>
#include <f3base/FilteredTimer.h>
#include <f3base/Log.h>
#include <f3input/Manager.h>
#include <f3input/IKeyListener.h>
#include <f3input/Joystick.h>
#include <f3graphics/DebugContext.h>

#include "SpaceShip.h"
#include "KeyboardSpaceShipController.h"
#include "JoystickSpaceShipController.h"
#include <f3input/MouseState.h>
#include "ProjectileManager.h"

//#include <f3filesystem/FileSystem.h>

//f3::TextNode textnode(&font, "EneMemY 2");


f3g::QuadMesh mesh;
f3s::MeshNode mn1(&mesh);


SpaceShip ship;
KeyboardSpaceShipController* ship_controller_kb;
JoystickSpaceShipController* ship_controller_js = NULL;


class testapp : public IApplication
{
public:
	f3::Animator* animation;
	void onInit() 
	{
		ship_controller_kb = new KeyboardSpaceShipController(&ship, (f3i::Keyboard*) f3i::manager._devices[0]);
		if (f3i::manager._devices.size() > 1)
			ship_controller_js = new JoystickSpaceShipController(&ship, (f3i::Joystick*) f3i::manager._devices[1]);
		f3::input::manager.registerListener(ship_controller_kb);
	}
	
	void print()
	{
		std::ostringstream os;
		os <<  "FPS: \n" << (1000/f3::util::timer.elapsed());
		f3g::debug.addText(f3m::Vector3f(-10,-9,0), os.str());
		f3g::debug.addText(f3m::Vector3f(-10, 9.5f,0), "ENEMEMY3", f3u::ColorRGBA(1,0,0,1.0f));
	}

	void onUpdate() 
	{
		Sleep(10);
		ship_controller_kb->update();

		if (ship_controller_js != NULL)
			ship_controller_js->update();

		print();
		
		mn1.position()._x = ship.position()._x;
		mn1.position()._y = ship.position()._y;
		mn1.rot += ship._angle;



		if (ship_controller_js != NULL)
		{
			f3::I32 val2 = ((f3i::Joystick*) f3i::manager._devices[1])->getAxesValue(3);

			f3::F32 f = val2 / 20000.0f;
			f3::I32 deadzone = 2500;

			if (val2 < -deadzone)
				f3s::graph.camera()->position()._z += 0.0015f*f;
			if (val2 > deadzone)
				f3s::graph.camera()->position()._z += 0.0015f*f;
		}

		f3i::MouseState ms = f3::input::manager.getMouseState();
		f3s::graph.camera()->position()._z += f3::util::timer.elapsed()*ms._relZ / 100.0f;

		ship.update(f3u::timer.elapsed());
		projectiles.update(f3u::timer.elapsed());
	}
	void onExit() {}
};

void main(int argc, const char* argv[])
{
	f3g::DeviceType devtype = f3g::DX10;

	if (argc == 3)
	{
		std::string cmd(argv[1]);
		std::string type(argv[2]);

		if (cmd.compare("-graphics") == 0)
		{
			if (type.compare("opengl") == 0)
				devtype = f3g::GL;
		}
	}
	
	f3s::MeshNode mn2(&mesh);

	mn2.setPosition(f3m::Vector3f(0.0f,0.0f,0.0f));
	mn1.setPosition(f3m::Vector3f(0.0f,0.0f,0.0f));
	f3s::graph.root()->append(&mn1);
	mn1.append(&mn2);
	
	testapp* app = new testapp();
	
	f3::start(app, devtype);

	return;
}