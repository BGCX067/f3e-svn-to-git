#include "WindowListener.h"

namespace f3
{
	namespace graphics
	{
		WindowListener::WindowListener(IDevice* device) 
		{
			_device = device; 
		}

		void WindowListener::onDestroy() 
		{
			_device->destroy(); 
		}

		void WindowListener::onDraw() 
		{
			_device->draw();
		}

		void WindowListener::onResize(int w, int h)
		{
			_device->resize(w, h);
		}
	}
}