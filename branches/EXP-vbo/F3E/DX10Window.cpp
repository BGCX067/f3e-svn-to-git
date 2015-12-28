#include "DX10Window.h"
#include "Log.h"

namespace msw
{
	void DX10Window::setFullscreen(bool fullscreen)
	{
		this->fullscreen = fullscreen;
		((graphics::dx10canvas*)_canvas)->setFullscreen(fullscreen);
	}

	void DX10Window::initRenderAPI()
	{
		Window::initRenderAPI();

		_canvas = new graphics::dx10canvas();

		((graphics::dx10canvas*)_canvas)->setFullscreen(fullscreen);
		((graphics::dx10canvas*)_canvas)->init(hWnd);
		_canvas->resize(_width, _height);
	}
}