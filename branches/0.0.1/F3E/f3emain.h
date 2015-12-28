#ifndef F3EMAIN_H
#define F3EMAIN_H

#include <stdio.h>
#include <windows.h>
#include <iostream>
#include <string>
#include <list>
#include <map>
#include <sstream>
#include <algorithm>
#include <iterator>
#include "wx/wx.h"
#include "F3EApplicationWindow.h"
#include "F3EIApplication.h"

#ifndef EXPORTDLL
#define DLL __declspec(dllimport)
#else 
#define DLL __declspec(dllexport)
#endif
//--------------------------------------------------------------------------------------
// Global Variables
//--------------------------------------------------------------------------------------
HINSTANCE               g_hInst = NULL;
HWND                    g_hWnd = NULL;
F3EIApplication* g_App;
//--------------------------------------------------------------------------------------
// Forward declarations
//--------------------------------------------------------------------------------------
LRESULT CALLBACK    WndProc( HWND, UINT, WPARAM, LPARAM );
int DLL WindowSetup();
LRESULT CALLBACK WindowProcedure(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);
void DLL WindowUpdate();
int DLL start(F3EIApplication* app);

wxAppConsole *wxCreateApp()                                            
{                                                                      
	wxAppConsole::CheckBuildOptions(WX_BUILD_OPTIONS_SIGNATURE,"your program");
    return new F3EApplicationWindow;                               
};

wxAppInitializer wxTheAppInitializer((wxAppInitializerFunction) wxCreateApp);

DECLARE_APP(F3EApplicationWindow)   

F3EApplicationWindow& wxGetApp()
{
	return *wx_static_cast(F3EApplicationWindow*, wxApp::GetInstance());
};

#endif