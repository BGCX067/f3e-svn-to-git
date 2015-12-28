#include "WindowBase.h"
#include <iostream>

namespace msw
{
	LRESULT CALLBACK WindowBase::msgRouter (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
	{
			WindowBase *wnd = 0;

			if (message == WM_NCCREATE) 
				SetWindowLong(hwnd, GWL_USERDATA, long((LPCREATESTRUCT(lParam))->lpCreateParams));

			wnd = (WindowBase*) GetWindowLong(hwnd, GWL_USERDATA);

			if (wnd)
				wnd->msgHandler(hwnd, message, wParam, lParam);
			else
				return DefWindowProc(hwnd, message, wParam, lParam);
	}
}