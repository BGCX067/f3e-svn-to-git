#ifndef MSW_WindowS_H
#define MSW_WindowS_H

#include <windows.h>
#include <string>
#include "WindowBase.h"
#include <map>
#include <f3base/IDevice.h>
#include "IWindowListener.h"

namespace f3
{
	class Window : WindowBase
	{
	protected:
		int _width;
		int _height;
		std::string _title;
		HDC			hDC;		// Private GDI Device Context
		HGLRC		hRC;		// Permanent Rendering Context
		HWND		hWnd;		// Holds Our Window Handle
		HINSTANCE	hInstance;		// Holds The Instance Of The Application

		bool	active;		// Window Active Flag Set To TRUE By Default
		bool	fullscreen;	// fullscreen Flag Set To fullscreen Mode By Default

	public:
		f3::graphics::IDevice* _device;
		enum RenderAPI { DIRECTX10, OPENGL };
		IWindowListener* _listener;

		Window(void);
		~Window(void);
		bool create(std::string title, int width, int height, int bits, bool fullscreenflag);
		void destroy();
		void setupFullscreen(int width, int height, int bits);
		LRESULT CALLBACK msgHandler(HWND hWnd,UINT uMsg,WPARAM wParam, LPARAM lParam);
		virtual void paint();
		virtual bool getFullscreen();
		void show();
		virtual void setFullscreen(bool);
		void setPosition(int x, int y);
		HWND Window::handle();
		int width() { return _width; };
		int height() { return _height; };
	};

}

#endif