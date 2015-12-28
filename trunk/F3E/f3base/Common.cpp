
#include "Stdafx.h"

#include "Common.h"

#include "Log.h"
#include "FilteredTimer.h"
#include <ctime>
#include "Window.h"

namespace f3
{

	namespace util
	{
		f3u::Log log;
		f3::Timer timer;

		//float time()
		//{
		//	LARGE_INTEGER frequency;        // ticks per second
		//	LARGE_INTEGER t;
		//	QueryPerformanceFrequency(&frequency);
		//	QueryPerformanceCounter(&t);
		//	return (float) t.LowPart / frequency.LowPart;
		//}
	}


	namespace platform
	{
		HWND hWnd = 0;
		
		Window* createWindow()
		{		
			Window* w = new Window();
			w->create("F3 Test" ,1000, 1000, 32, false);
			w->setPosition(0,0);
			return w;
		}


		void callback(bool& done, f3::Window* w)
		{
			MSG msg;									

			if (PeekMessage(&msg,NULL,0,0,PM_REMOVE))	
			{
				if (msg.message==WM_QUIT)				
				{
					done=TRUE;							
				}
				else								
				{
					TranslateMessage(&msg);			
					DispatchMessage(&msg);			
				}
			}
		}


	}
}