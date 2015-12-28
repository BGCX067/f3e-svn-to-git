
#include "Stdafx.h"

#include "WindowBase.h"
#include <iostream>

namespace f3
{
	LRESULT CALLBACK WindowBase::msgRouter (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
	{
			WindowBase *wnd = 0;

			if (message == WM_NCCREATE)
			{
#ifdef _M_X64
				SetWindowLongPtr(hwnd, GWLP_USERDATA, long((LPCREATESTRUCT(lParam))->lpCreateParams));
#else 
				SetWindowLong(hwnd, GWL_USERDATA, long((LPCREATESTRUCT(lParam))->lpCreateParams));
#endif
			}

			#ifdef _M_X64
			wnd = (WindowBase*) GetWindowLong(hwnd, GWLP_USERDATA);
#else 
			wnd = (WindowBase*) GetWindowLong(hwnd, GWL_USERDATA);
#endif
			if (wnd)
				return wnd->msgHandler(hwnd, message, wParam, lParam);
			
			return DefWindowProc(hwnd, message, wParam, lParam);
	}
}