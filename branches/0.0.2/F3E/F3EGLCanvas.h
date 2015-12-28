#ifndef F3EGLCanvas_H
#define F3EGLCanvas_H

#ifndef EXPORTDLL
#define DLL __declspec(dllimport)
#else 
#define DLL __declspec(dllexport)
#endif

#include "wx/wx.h"
#include "wx/glcanvas.h"

class F3EGLCanvas : public wxGLCanvas 
{
	void Render();

public:
    F3EGLCanvas(wxFrame* parent);
    void Paintit(wxPaintEvent& event);
	void F3EGLCanvas::Resized(wxSizeEvent& evt);

protected:
    DECLARE_EVENT_TABLE()
};

#endif