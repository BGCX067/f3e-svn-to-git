#include "F3EGLCanvas.h"
#include <iostream>

BEGIN_EVENT_TABLE(F3EGLCanvas, wxGLCanvas)
    EVT_PAINT	(F3EGLCanvas::Paintit)
	EVT_SIZE	(F3EGLCanvas::Resized)
END_EVENT_TABLE()
 
F3EGLCanvas::F3EGLCanvas(wxFrame *parent) : wxGLCanvas(parent, wxID_ANY,  wxDefaultPosition, wxDefaultSize, 0, wxT("GLCanvas"))
{
    int argc = 1;
    char* argv[1] = { wxString((wxTheApp->argv)[0]).char_str() };
    //glutInit(&argc, argv);
}

void F3EGLCanvas::Paintit(wxPaintEvent& WXUNUSED(event))
{
	wxPaintDC pdc(this);
	pdc.Clear();

    Render();
}
 
void F3EGLCanvas::Render()
{
    SetCurrent();
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT);
    glViewport(0, 0, (GLint)GetSize().x, (GLint)GetSize().y);
 std::cout << GetTickCount() << " resized " << GetSize().x << " " << GetSize().y << std::endl;
	
    glBegin(GL_POLYGON);
        glColor3f(1.0, 1.0, 1.0);
        glVertex2f(-0.5, -0.5);
        glVertex2f(-0.5, 0.5);
        glVertex2f(0.5, 0.5);
        glVertex2f(0.5, -0.5);
        glColor3f(0.4, 0.5, 0.4);
        glVertex2f(0.0, -0.8);
    glEnd();
 
    glBegin(GL_POLYGON);
        glColor3f(1.0, 0.0, 0.0);
        glVertex2f(0.1, 0.1);
        glVertex2f(-0.1, 0.1);
        glVertex2f(-0.1, -0.1);
        glVertex2f(0.1, -0.1);
    glEnd();
 
 
    glFlush();
    SwapBuffers();
} 

void F3EGLCanvas::Resized(wxSizeEvent& evt)
{
	Render();
	wxGLCanvas::OnSize(evt);
	
	Update();
}
 
