#ifndef F3EMAIN_H
#define F3EMAIN_H

#include <f3base/Common.h>
#include <f3base/IApplication.h>


namespace f3
{
	
	int DLL start(IApplication* app, f3g::DeviceType devicetype);

	class Window;

	namespace graphics 
	{
		class Device;
	}

	namespace input
	{
		class Manager;
		class EventHandler;

		extern DLL Manager manager;
	}
	namespace scene
	{
	}
	namespace platform
	{
		extern HWND hWnd;
		Window* createWindow();
		graphics::Device* createDevice(f3::Window* window);
		void callback(bool& done, f3::Window* window);
	}

}
#endif