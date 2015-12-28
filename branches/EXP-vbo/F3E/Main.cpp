#define EXPORTDLL

#include "Main.h"

#include <iostream>
#include "Vector.h"
#include <windows.h>
#include "Window.h"
#include "GLWindow.h"
#include "DX10Window.h"
#include "Mesh.h"
#include "MeshNode.h"
#include "Scene.h"
#include "Matrix.h"

//
//wxAppInitializer wxTheAppInitializer((wxAppInitializerFunction) wxCreateApp);
//
//wxAppConsole *wxCreateApp();
//F3EApplicationWindow& wxGetApp();


BOOL WINAPI DllMain( HINSTANCE hDLL, DWORD dwReason, LPVOID lpReserved)
{
	switch (dwReason)
	{
		case DLL_PROCESS_ATTACH:
		break;

		case DLL_THREAD_ATTACH:
		break;

		case DLL_THREAD_DETACH:
		break;

		case DLL_PROCESS_DETACH:
		break;
	}

	return TRUE;
}

namespace f3e 
{
int DLL start(IApplication* app)
{
	f3m::Matrix4f matrix;
	
	
	//f3m::Vector3<float> v1(8.0f, 1.0f, 2.0f);
	//f3m::Vector3<float> v2(3.0f, 1.0f, 2.5f);
	//
	//matrix.translate(f3m::Vector3f(1,1,1));
	//std::cout << "m: " << (std::string)matrix << std::endl;

	
	int argc = 0;
	app->OnInit();

	MSG msg;									
	BOOL done = FALSE;								

	msw::Window* w = new msw::GLWindow();
	//msw::Window* w = new msw::DX10Window();
	w->create("F3 Test", 600, 600, 32, false);
	w->initRenderAPI();
	w->show();
	
	f3::Mesh mesh;
	f3::MeshNode mn(&mesh);
	mn.append(new f3::MeshNode(&mesh));
	mn.setPosition(f3m::Vector3f(0.1f,0.1f,0.1f));
	f3::Scene::getDefault()->root()->append(&mn);
	//f3::Scene::getDefault()->root()->append(new f3::Node());
	//f3::Scene::getDefault()->root()->append(new f3::Node());

	//std::cout << f3::Scene::getDefault()->root()->toString() << std::endl;	
	//std::cout << mn.toString() << std::endl;

	while(!done)									
	{
		if (PeekMessage(&msg,NULL,0,0,PM_REMOVE))	
		{
			if (msg.message==WM_QUIT)				
			{
				done=TRUE;							
			}
			else if (msg.message == WM_KEYDOWN)
			{
				switch (msg.wParam)
				{
				//case VK_F1:
				//	w->initRenderAPI(msw::window::DIRECTX10);
				//	break;
				case VK_F2:
					w->shutdownRenderAPI();
					break;
				//case VK_F3:
				//	if (w->getFullscreen() == false)
				//	{
				//		w->destroy();
				//		delete w;
				//		w = new msw::Window();
				//		w->create("test",1920,1200,32, true);
				//		w->show();
				//		w->initRenderAPI();
				//	}
				//	else
				//	{
				//		w->destroy();
				//		delete w;
				//		w = new msw::Window();
				//		w->create("test",1200,768,32, false);
				//		w->show();
				//		w->initRenderAPI();
	
				//	}
				//	break;
				case VK_F4:
					if (w->getFullscreen() == false)
					{
						w->setFullscreen(true);
						//w->destroy();
						//delete w;
						//w = new msw::Window();
						//w->create("etest",1920,1200,32, true, msw::Window::OPENGL);
					}
					else
					{
						w->setFullscreen(false);
					}
					break;
				}
			}
			else								
			{
				TranslateMessage(&msg);			
				DispatchMessage(&msg);			
			}
		}
		else									
		{
			w->paint();
		}
	}
	
	w->destroy();
	return 0;//wxEntry(0 /*hInstance*/);//, hPrevInstance, lpCmdLine, nCmdShow);
}
}
