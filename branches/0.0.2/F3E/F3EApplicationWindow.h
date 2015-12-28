#ifndef F3EApplicationWindow_H
#define F3EApplicationWindow_H

#ifndef EXPORTDLL
#define DLL __declspec(dllimport)
#else 
#define DLL __declspec(dllexport)
#endif

#include "wx/wx.h"
#include "wx/glcanvas.h"

class DLL F3EApplicationWindow : public wxApp
{
	wxGLCanvas* glCanvas;

public:
	virtual bool OnInit();
	void Render();
}; 

//////////////////////////////////////////////////////////////////77777



#endif 