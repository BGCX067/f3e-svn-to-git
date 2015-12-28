#ifndef F3EMAIN_H
#define F3EMAIN_H

#ifndef EXPORTDLL
#define DLL __declspec(dllimport)
#else 
#define DLL __declspec(dllexport)
#endif

//#include <windows.h>
#include "wx/wx.h"
#include "F3EIApplication.h"
#include "vector.h"
//--------------------------------------------------------------------------------------
// Forward declarations
//--------------------------------------------------------------------------------------

namespace f3e
{
	int DLL start(F3EIApplication* app);
}


//DECLARE_APP(F3EApplicationWindow)   

#endif