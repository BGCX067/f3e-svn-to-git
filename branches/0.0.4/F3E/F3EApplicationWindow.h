#ifndef F3EApplicationWindow_H
#define F3EApplicationWindow_H

#ifndef EXPORTDLL
#define DLL __declspec(dllimport)
#else 
#define DLL __declspec(dllexport)
#endif

#include "wx/wx.h"
#include "F3EGLCanvas.h"

class F3EApplicationWindow : public wxApp
{
	F3EGLCanvas* glCanvas;

public:
	virtual bool OnInit();
	void Render();
}; 

//////////////////////////////////////////////////////////////////77777



#endif 