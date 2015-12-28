#ifndef F3EApplicationWindow_H
#define F3EApplicationWindow_H
 
#include "wx/wx.h"
#ifndef EXPORTDLL
#define DLL __declspec(dllimport)
#else 
#define DLL __declspec(dllexport)
#endif

// The HelloWorldApp class. This class shows a window
// containing a statusbar with the text "Hello World"
class DLL F3EApplicationWindow : public wxApp
{
public:
	virtual bool OnInit();

}; 

 
#endif 