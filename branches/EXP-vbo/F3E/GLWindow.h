#ifndef MSW_GLWINDOW_H
#define MSW_GLWINDOW_H

#include <windows.h>
#include <string>
#include "Window.h"
#include <map>
#include "ICanvas.h"
#include "GLCanvas.h"
#include "dx10canvas.h"

namespace msw
{
	class GLWindow : public msw::Window
	{

	public:
		void setFullscreen(bool);
		void initRenderAPI();
		void shutdownRenderAPI();
		void paint();
	};

}

#endif