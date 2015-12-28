#include "GLWindow.h"
#include "Log.h"

namespace msw
{
	void GLWindow::setFullscreen(bool fullscreen)
	{
		destroy();
		create(_title, 1920, 1200, 32, fullscreen);
		initRenderAPI();
		show();
	}

	void GLWindow::initRenderAPI()
	{
		unsigned int PixelFormat;

		static	PIXELFORMATDESCRIPTOR pfd =				// pfd Tells Windows How We Want Things To Be
		{
			sizeof(PIXELFORMATDESCRIPTOR),				// Size Of This Pixel Format Descriptor
			1,											// Version Number
			PFD_DRAW_TO_WINDOW |						// Format Must Support Window
			PFD_SUPPORT_OPENGL |						// Format Must Support OpenGL
			PFD_DOUBLEBUFFER,							// Must Support Double Buffering
			PFD_TYPE_RGBA,								// Request An RGBA Format
			32,										// Select Our Color Depth
			0, 0, 0, 0, 0, 0,							// Color Bits Ignored
			0,											// No Alpha Buffer
			0,											// Shift Bit Ignored
			0,											// No Accumulation Buffer
			0, 0, 0, 0,									// Accumulation Bits Ignored
			32,											// 16Bit Z-Buffer (Depth Buffer)  
			0,											// No Stencil Buffer
			0,											// No Auxiliary Buffer
			PFD_MAIN_PLANE,								// Main Drawing Layer
			0,											// Reserved
			0, 0, 0										// Layer Masks Ignored
		};
		
		if (!(hDC=GetDC(hWnd)))							// Did We Get A Device Context?
		{
			destroy();								// Reset The Display
			Log::getDefault()->warning("Can't create a GL device context.");
		}

		if (!(PixelFormat = ChoosePixelFormat(hDC, &pfd)))	// Did Windows Find A Matching Pixel Format?
		{
			destroy();								// Reset The Display
			Log::getDefault()->warning("Can't find a suitable pixelformat.");
			return;								// Return FALSE
		}

		if(!SetPixelFormat(hDC, PixelFormat, &pfd))		// Are We Able To Set The Pixel Format?
		{
			destroy();								// Reset The Display
			Log::getDefault()->warning("Can't set the pixelformat.");
			return;								// Return FALSE
		}

		if (!(hRC=wglCreateContext(hDC)))				// Are We Able To Get A Rendering Context?
		{
			destroy();								// Reset The Display
			Log::getDefault()->warning("Can't create a GL rendering context.");
		}

		if(!wglMakeCurrent(hDC, hRC))					// Try To Activate The Rendering Context
		{
			destroy();								// Reset The Display
			Log::getDefault()->warning("Can't activate the GL rendering context.");
		}

		Window::initRenderAPI();
		_canvas = new graphics::GLCanvas();
		((graphics::GLCanvas*)_canvas)->init();
		_canvas->resize(_width, _height);
	}

	void GLWindow::shutdownRenderAPI()
	{
		if (fullscreen)
		{		
			ChangeDisplaySettings(NULL, 0);
			ShowCursor(TRUE);
		}

		if (hRC)
		{
			if (!wglMakeCurrent(NULL,NULL))	
				Log::getDefault()->warning("Release of DC and RC failed.");

			if (!wglDeleteContext(hRC))						
				Log::getDefault()->warning("Release rendering context failed.");
			
			hRC = NULL;
		}

		// Are We Able To Release The DC
		if (hDC && !ReleaseDC(hWnd,hDC))
		{
			Log::getDefault()->warning("Release device context failed.");
			hDC = NULL;
		}

		Window::shutdownRenderAPI();
	}

	void GLWindow::paint()
	{
		if (_canvas != NULL)
		_canvas->draw();

		SwapBuffers(hDC);
	}
}