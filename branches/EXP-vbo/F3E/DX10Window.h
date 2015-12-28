#ifndef MSW_DX10Window_H
#define MSW_DX10Window_H

#include <windows.h>
#include <string>
#include "Window.h"
#include <map>
#include "ICanvas.h"
#include "GLCanvas.h"
#include "dx10canvas.h"

namespace msw
{
	class DX10Window : public msw::Window
	{

	public:
		void setFullscreen(bool);
		void initRenderAPI();
	};

}

#endif