#ifndef MSW_GLWINDOW_H
#define MSW_GLWINDOW_H

#include <windows.h>
#include <string>
#include <f3base/Window.h>
#include <map>
#include <f3base/IDevice.h>
#include "GLDevice.h"

namespace f3
{
	namespace graphics
	{
		class GLW32Device : public GLDevice
		{
			bool fullscreen;
			HDC			hDC;		// Private GDI Device Context
			HGLRC		hRC;		// Permanent Rendering Context

		public:
			GLW32Device(Window* window);
			~GLW32Device(void);

			void setFullscreen(bool);
			void init();
			void destroy();
			void draw();
		};
	}
}

#endif