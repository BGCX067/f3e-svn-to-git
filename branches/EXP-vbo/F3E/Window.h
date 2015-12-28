#ifndef MSW_WindowS_H
#define MSW_WindowS_H

#include <windows.h>
#include <string>
#include "WindowBase.h"
#include <map>
#include "ICanvas.h"
#include "GLCanvas.h"
#include "dx10canvas.h"

namespace msw
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

		bool	keys[256];			// Array Used For The Keyboard Routine
		bool	active;		// Window Active Flag Set To TRUE By Default
		bool	fullscreen;	// Fullscreen Flag Set To Fullscreen Mode By Default

	public:
		graphics::ICanvas* _canvas;
		enum RenderAPI { DIRECTX10, OPENGL };

		Window(void);
		~Window(void);
		bool create(std::string title, int width, int height, int bits, bool fullscreenflag);
		void destroy();
		void setupFullscreen(int width, int height, int bits);
		LRESULT CALLBACK msgHandler(HWND hWnd,UINT uMsg,WPARAM wParam, LPARAM lParam);
		virtual void paint();
		virtual void initRenderAPI();
		void shutdownRenderAPI();
		virtual bool getFullscreen();
		void show();
		virtual void setFullscreen(bool);
	};

}

#endif