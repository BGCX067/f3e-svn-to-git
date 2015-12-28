#ifndef F3EMAIN_H
#define F3EMAIN_H

#ifndef EXPORTDLL
#define DLL __declspec(dllimport)
#else 
#define DLL __declspec(dllexport)
#endif

#include <windows.h>
#include "wx/wx.h"
#include "F3EApplicationWindow.h"
#include "F3EIApplication.h"

//--------------------------------------------------------------------------------------
// Global Variables
//--------------------------------------------------------------------------------------
HINSTANCE               g_hInst = NULL;
HWND                    g_hWnd = NULL;
//F3EIApplication*		g_App = 0;

//--------------------------------------------------------------------------------------
// Forward declarations
//--------------------------------------------------------------------------------------

int DLL start(F3EIApplication* app);



DECLARE_APP(F3EApplicationWindow)   

wxAppConsole *wxCreateApp();
F3EApplicationWindow& wxGetApp();

#endif