#ifndef WindowListener_h__
#define WindowListener_h__

#include <f3base/IDevice.h>
#include <f3base/IWindowListener.h>

namespace f3
{
	namespace graphics
	{

		class WindowListener : public IWindowListener
		{
			IDevice* _device;

		public:
			WindowListener(IDevice* device);
			inline void onDestroy();
			inline void onDraw();
			inline void onResize(int w, int h);
		};

	}
}

#endif // WindowListener_h__
