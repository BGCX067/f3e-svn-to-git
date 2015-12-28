#define EXPORTDLL

#include "F3EMain.h"
#include "wx/wx.h"

#include <iostream>
#include "F3EApplicationWindow.h"
#include "vector.h"

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
int DLL start(F3EIApplication* app)
{
	f3m::vector3<float> v1(8.0f, 1.0f, 2.0f);
	f3m::vector3<float> v2(3.0f, 1.0f, 2.5f);
	
	std::cout << "rslt: " << (v1-v2*v2).toString() << std::endl;

	int argc = 0;
	app->OnInit();
	// MyWxApp derives from wxApp
	wxApp::SetInstance( new F3EApplicationWindow() );
	wxEntryStart( argc, NULL );
	wxTheApp->OnInit();

	// you can create top level-windows here or in OnInit()

	// do your testing here

	wxTheApp->OnRun();
	wxTheApp->OnExit();
	wxEntryCleanup();

	return 0;//wxEntry(0 /*hInstance*/);//, hPrevInstance, lpCmdLine, nCmdShow);
}
}

wxAppConsole *wxCreateApp()                                            
{                                                                      
	wxAppConsole::CheckBuildOptions(WX_BUILD_OPTIONS_SIGNATURE,"your program");
    return new F3EApplicationWindow;                               
}

F3EApplicationWindow& wxGetApp()
{
	return *wx_static_cast(F3EApplicationWindow*, wxApp::GetInstance());
}
