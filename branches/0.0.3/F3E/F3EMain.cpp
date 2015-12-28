#define EXPORTDLL

#include "F3EMain.h"
#include <iostream>

wxAppInitializer wxTheAppInitializer((wxAppInitializerFunction) wxCreateApp);

wxAppConsole *wxCreateApp();
F3EApplicationWindow& wxGetApp();


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

int DLL start(F3EIApplication* app)
{
	app->OnInit();
	
	return wxEntry(0 /*hInstance*/);//, hPrevInstance, lpCmdLine, nCmdShow);
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
