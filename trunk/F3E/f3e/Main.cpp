#include "Main.h"

#include <f3base/Common.h>
#include <f3base/Window.h>
#include <f3base/FilteredTimer.h>
#include <f3input/Manager.h>
#include <f3scene/Graph.h>
#include <f3graphics/DebugContext.h>
#include <f3graphics/Device.h>
#include <f3graphics-gl/GLW32Device.h>
#include <f3graphics-dx10/DX10Device.h>




namespace f3
{
	namespace input
	{
		Manager manager;
	}

	namespace platform
	{
		graphics::Device* createDevice( Window* window )
		{
			graphics::Device* device = NULL;
			//graphics::Device* device = new f3::graphics::GLW32Device(window);
			//graphics::Device* device = new f3::graphics::DX10Device(window);
			return device;
		}
	}


	int start(IApplication* app, f3g::DeviceType devicetype)
	{

		bool done = FALSE;

		f3::Window* w = f3::platform::createWindow();
		f3g::Device* d = NULL;
		/*devicetype == f3g::DX10 ? d = new f3g::DX10Device(w) :*/ d = new f3g::GLW32Device(w);// f3::platform::createDevice(w);

		d->init();
		w->show();

		f3::input::manager.init();
		
		f3u::timer.start();

		f3g::debug.addLine(f3m::Vector3f(0,0,0), f3m::Vector3f(1,1,0));

		app->onInit();

		while (!done)
		{
			f3::platform::callback(done, w);
			f3u::timer.stop();
			f3u::timer.start();
			
			//std::ostringstream os;
			//os << "ms: " << (f3::util::timer.elapsed());
			//f3::util::log.info(os.str());
			
			f3::input::manager.update();
			
			app->onUpdate();
			if (w != NULL)
			{
				w->paint();
			}
		}

		w->destroy();

		delete d;

		return 0;
	}


}
