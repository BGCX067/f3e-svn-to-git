#pragma once
#include <windows.h>

namespace msw
{

class WindowBase
{
protected:
	// window handle
	HWND _hwnd;

public:
	WindowBase () {}

	// this will be WNDCLASSEX::lpfnWndProc
	static LRESULT CALLBACK msgRouter (HWND, UINT, WPARAM, LPARAM);

	// this is the actual window procedure
	// this will be implemented in derived classes and will be called by msgRouter
	virtual LRESULT CALLBACK msgHandler (HWND, UINT, WPARAM, LPARAM) = 0;

	// calls CreateWindowEx, creating the window

	// ... other member functions ...

};

}