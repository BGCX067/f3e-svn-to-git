#include "GLW32Device.h"
#include <f3base/Log.h>

#include <gl/wglew.h>
#include <gl/glew.h>

namespace f3
{	
	namespace graphics
	{

		GLW32Device::GLW32Device( Window* window ) : GLDevice(window)
		{

		}

		GLW32Device::~GLW32Device( void )
		{

		}

		void GLW32Device::setFullscreen(bool fullscreen)
		{
			//destroy();
			//create(_title, 1920, 1200, 32, fullscreen);
			//initRenderAPI();
			//show();
		}

		void GLW32Device::init()
		{
			f3u::log << f3u::info << "Initializing GL Device (Win32)" << f3u::endl;


			unsigned int PixelFormat;

			static	PIXELFORMATDESCRIPTOR pfd =				// pfd Tells Windows How We Want Things To Be
			{
				sizeof(PIXELFORMATDESCRIPTOR),				// Size Of This Pixel Format Descriptor
				1,											// Version Number
				PFD_DRAW_TO_WINDOW |						// Format Must Support Window
				PFD_SUPPORT_OPENGL |						// Format Must Support OpenGL
				PFD_DOUBLEBUFFER,							// Must Support Double Buffering
				PFD_TYPE_RGBA,								// Request An RGBA Format
				32,											// Select Our Color Depth
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

			if (!(hDC=GetDC(_window->handle())))							// Did We Get A Device Context?
			{
				f3::util::log.warning("Can't create a GL device context.");
			}

			if (!(PixelFormat = ChoosePixelFormat(hDC, &pfd)))	// Did Windows Find A Matching Pixel Format?
			{
				f3::util::log.warning("Can't find a suitable pixel format.");
				return;								// Return FALSE
			}

			if(!SetPixelFormat(hDC, PixelFormat, &pfd))		// Are We Able To Set The Pixel Format?
			{
				f3::util::log.warning("Can't set the pixel format.");
				return;								// Return FALSE
			}
			

			if (!(hRC=wglCreateContext(hDC)))				// Are We Able To Get A Rendering Context?
			{							// Reset The Display
				f3::util::log.warning("Can't create a GL rendering context.");
			}

			if(!wglMakeCurrent(hDC, hRC))					// Try To Activate The Rendering Context
			{								// Reset The Display
				f3u::log << f3u::warning << "Can't activate the GL rendering context." << f3u::endl;
			}
			

			HGLRC m_hrc;
			/*if(wglewIsSupported("WGL_create_context") == 1)
			{
				HGLRC hRC2 = NULL;
				hRC2 = wglCreateContextAttribsARB(hDC,0, attribs);
				wglMakeCurrent(NULL,NULL);
				wglDeleteContext(hRC);
				wglMakeCurrent(hDC, hRC2);
				hRC = hRC2;
				}*/
			
			int attribs[] =
			{
				WGL_CONTEXT_MAJOR_VERSION_ARB, 3,
				WGL_CONTEXT_MINOR_VERSION_ARB, 3, 
				WGL_CONTEXT_FLAGS_ARB, WGL_CONTEXT_DEBUG_BIT_ARB,         
				WGL_CONTEXT_PROFILE_MASK_ARB, WGL_CONTEXT_COMPATIBILITY_PROFILE_BIT_ARB,
				/*WGL_CONTEXT_PROFILE_MASK_ARB, WGL_CONTEXT_CORE_PROFILE_BIT_ARB,*/
				0
			};
			PFNWGLCREATECONTEXTATTRIBSARBPROC wglCreateContextAttribsARB = NULL;
			wglCreateContextAttribsARB = (PFNWGLCREATECONTEXTATTRIBSARBPROC)				wglGetProcAddress("wglCreateContextAttribsARB");
			
			m_hrc = wglCreateContextAttribsARB(hDC,0, attribs);
			wglMakeCurrent(NULL,NULL);
			wglDeleteContext(hRC); 
			wglMakeCurrent(hDC, m_hrc);		
			

			GLenum err = 0;
			err = glewInit();

			if (GLEW_OK != err)
			{
				f3u::log << f3u::info << "GLEW: is not initialized!" << f3u::endl;
			}
			else
			{
				f3u::log << f3u::info << "GLEW: initialized!" << f3u::endl;
			}


			GLDevice::init();
		}

		void GLW32Device::destroy()
		{
			if (fullscreen)
			{		
				ChangeDisplaySettings(NULL, 0);
				ShowCursor(TRUE);
			}

			if (hRC)
			{
				if (!wglMakeCurrent(NULL,NULL))	
					f3u::log.warning("Release of DC and RC failed.");

				if (!wglDeleteContext(hRC))						
					f3u::log.warning("Release rendering context failed.");

				hRC = NULL;
			}

			// Are We Able To Release The DC
			if (hDC && !ReleaseDC(_window->handle(),hDC))
			{
				f3::util::log.warning("Release device context failed.");
				hDC = NULL;
			}

		}

		void GLW32Device::draw()
		{
			GLDevice::draw();
			SwapBuffers(hDC);
		}

	}
}