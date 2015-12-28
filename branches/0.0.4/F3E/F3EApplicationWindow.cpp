#include "F3EApplicationWindow.h"
#include "F3EGLCanvas.h"

bool F3EApplicationWindow::OnInit() 
{
	int attrib[2]; 

    attrib[0] = WX_GL_DEPTH_SIZE; 
    attrib[1] = 32; 
	
	wxFrame *frame = new wxFrame((wxFrame *)NULL, -1,  "F3E Sample Window", wxPoint(50,50), wxSize(1200,700) ); 
	glCanvas = new F3EGLCanvas(frame);
	frame->Show(true); 
	//frame->ShowFullScreen(true);
	
	// @@@ Create a second Window @@@
	//wxFrame *frame2 = new wxFrame((wxFrame *)NULL, -1,  "F3E Sample Window", wxPoint(50,50), wxSize(450,450) ); 
	//new F3EGLCanvas(frame2);
	//frame2->Show(true);
	
	return true;
}