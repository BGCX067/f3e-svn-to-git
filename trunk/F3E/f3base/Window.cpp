
#include "Stdafx.h"

#include "Window.h"
#include "Common.h"

namespace f3
{

Window::Window(void) : _listener(NULL)
{
	_device = NULL;

}

Window::~Window(void)
{
}

void Window::destroy()
{

	// Are We Able To Destroy The Window?
	if (hWnd && !DestroyWindow(hWnd))
	{
		f3::util::log.warning("Could not release hWnd.");
		hWnd = NULL;
	}

	// Are We Able To Unregister Class
	if (!UnregisterClass(_title.c_str(),hInstance))			
	{
		f3::util::log.warning("Could not unregister class.");
		hInstance = NULL;
	}

}

void Window::setupFullscreen(int width, int height, int bits)
{
	// Device Mode
	DEVMODE settings;

	memset(&settings,0,sizeof(settings));
	settings.dmSize = sizeof(settings);
	settings.dmPelsWidth = width;
	settings.dmPelsHeight = height;
	settings.dmBitsPerPel = bits; // Selected Bits Per Pixel
	settings.dmFields = DM_BITSPERPEL|DM_PELSWIDTH|DM_PELSHEIGHT;

	if (ChangeDisplaySettings(&settings,CDS_FULLSCREEN) != DISP_CHANGE_SUCCESSFUL)
		throw std::exception("could not switch to fullscreen");
}

void Window::setPosition(int x, int y)
{
	MoveWindow(hWnd, x, y, _width, _height, true);
}

bool Window::create(std::string title, int width, int height, int bits, bool fullscreenflag)
{
	_title = title;
	_width = width;
	_height = height;
	WNDCLASS	wc;			// Windows Class Structure
	DWORD		dwExStyle;	// Window Extended Style
	DWORD		dwStyle;	// Window Style
	RECT		WindowRect;			
	WindowRect.left = (long) 0;
	WindowRect.top = (long) 0;
	WindowRect.right = (long) width;
	WindowRect.bottom = (long) height;

	fullscreen = fullscreenflag;
	
	hInstance			= GetModuleHandle(NULL);				// Grab An Instance For Our Window
	wc.style			= CS_HREDRAW | CS_VREDRAW | CS_OWNDC;	// Redraw On Size, And Own DC For Window.
	wc.lpfnWndProc		= (WNDPROC) Window::msgRouter;					// WndProc Handles Messages
	wc.cbClsExtra		= 0;									// No Extra Window Data
	wc.cbWndExtra		= 0;									// No Extra Window Data
	wc.hInstance		= hInstance;							// Set The Instance
	wc.hIcon			= LoadIcon(NULL, IDI_WINLOGO);			// Load The Default Icon
	wc.hCursor			= LoadCursor(NULL, IDC_ARROW);			// Load The Arrow Pointer
	wc.hbrBackground	= NULL;									// No Background Required For GL
	wc.lpszMenuName		= NULL;									// We Don't Want A Menu
	wc.lpszClassName	= title.c_str();						// Set The Class Name

	if (!RegisterClass(&wc))									// Attempt To Register The Window Class
	{
		f3::util::log.warning("Failed to register the window class.");
		return false;
	}
	
	if (fullscreen)												// Attempt Fullscreen Mode?
	{
		setupFullscreen(width, height, bits);
		dwExStyle=WS_EX_APPWINDOW;								// Window Extended Style
		dwStyle=WS_POPUP;										// Windows Style
		//ShowCursor(FALSE);										// Hide Mouse Pointer
	}
	else
	{
		dwExStyle = WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;
		dwStyle = WS_OVERLAPPEDWINDOW;
	}

	
	// Create The Window
	if (!(hWnd = CreateWindowEx(dwExStyle,							// Extended Style For The Window
								title.c_str(),							// Class Name
								title.c_str(),								// Window Title
								dwStyle |							// Defined Window Style
								WS_CLIPSIBLINGS | WS_CLIPCHILDREN, 
								0, 0,		// Window Position
								WindowRect.right-WindowRect.left,	// Calculate Window Width
								WindowRect.bottom-WindowRect.top,	// Calculate Window Height
								NULL,								// No Parent Window
								NULL,								// No Menu
								hInstance,							// Instance
								this)))								// Dont Pass Anything To WM_CREATE
	{
		destroy();								// Reset The Display
		f3::util::log.warning("Window Creation Error.");
		return false;								// Return FALSE
	}

	f3::platform::hWnd = hWnd;

	//AdjustWindowRectEx(&WindowRect, dwStyle, FALSE, dwExStyle);		// Adjust Window To True Requested Size

	return true;
}

void Window::show()
{
	ShowWindow(hWnd,SW_SHOW);
	SetForegroundWindow(hWnd);
	SetFocus(hWnd);
}

void Window::paint()
{
	if(_listener != NULL)
		_listener->onDraw();
}

bool Window::getFullscreen()
{
	return fullscreen;
}

void Window::setFullscreen(bool enabled)
{
	fullscreen = enabled;
}

HWND Window::handle()
{
	return hWnd;
}

LRESULT CALLBACK Window::msgHandler(HWND hWnd, UINT	uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)								
	{
		case WM_ACTIVATE:						
		{
			if (!HIWORD(wParam))				
				active=TRUE;					
			else
				active=FALSE;					
			return 0;							
		}

		case WM_CLOSE:							
		{
			PostQuitMessage(0);					
			return 0;							
		}

		case WM_SIZE:
		{
			if (_listener != NULL)
				_listener->onResize(LOWORD(lParam),HIWORD(lParam));

			return 0;
		}
	}

	return DefWindowProc(hWnd,uMsg,wParam,lParam);
}

}