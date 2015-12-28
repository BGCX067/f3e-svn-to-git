#include "F3EApplicationWindow.h"
#include "F3EGLCanvas.h"

bool F3EApplicationWindow::OnInit() 
{
	int attrib[2]; 

    attrib[0] = WX_GL_DEPTH_SIZE; 
    attrib[1] = 32; 
	
	wxFrame *frame = new wxFrame((wxFrame *)NULL, -1,  "F3E Sample Window", wxPoint(50,50), wxSize(450,450) ); 
	wxFrame *frame2 = new wxFrame((wxFrame *)NULL, -1,  "F3E Sample Window", wxPoint(50,50), wxSize(450,450) ); 
	
	glCanvas = new F3EGLCanvas(frame);
	new F3EGLCanvas(frame2);

		//wxGLCanvas(frame, -1, wxPoint(0,0), wxSize(400,400), wxBORDER, _("some text")); 
	frame->Show(TRUE); 
	frame2->Show(true);
	
	return TRUE; 
} 
//
//void F3EApplicationWindow::Render()
//{
//	glCanvas->SetCurrent(); 
//	
//	//sleep(1); 
//	//..or try this instead 
//	glClearColor(0.0, 0.0, 0.0, 0.0); 
//	glClear(GL_COLOR_BUFFER_BIT); 
//	glViewport(50, 50, (GLint)100, (GLint)100); 
//	glLoadIdentity(); 
//	glTranslatef(0.0f,1.0f,0.0f); 
//
//	glColor3f(1.0, 1.0, 1.0); 
//
//	glBegin(GL_TRIANGLES); 
//	glColor3f(1.0f,0.0f,0.0f);      // Set The Color To Red 
//	glVertex3f( 0.0f, 1.0f, 0.0f);  // Move Up One Unit From Center (Top Point) 
//	glColor3f(0.0f,1.0f,0.0f);      // Set The Color To Green 
//	glVertex3f(-1.0f,-1.0f, 0.0f);  // Left And Down One Unit (Bottom Left) 
//	glColor3f(0.0f,0.0f,1.0f);      // Set The Color To Blue 
//	glVertex3f( 1.0f,-1.0f, 0.0f);	// Right And Down One Unit (Bottom Right) 
//	glEnd();                        // Done Drawing A Triangle 
//
////  glTranslatef(1.5f,0.0f,0.0f);   // From Right Point Move 3 Units Right 
//  
///*  glBegin(GL_QUADS); 
//    glVertex3f(-1.0f, 1.0f, 0.0f);  // Left And Up 1 Unit (Top Left) 
//    glVertex3f( 1.0f, 1.0f, 0.0f);  // Right And Up 1 Unit (Top Right) 
//    glVertex3f( 1.0f,-1.0f, 0.0f);  // Right And Down One Unit (Bottom Right) 
//	glVertex3f(-1.0f,-1.0f, 0.0f);  // Left And Down One Unit (Bottom Left) 
//	glEnd();*/ 
//	glFlush(); 
//
//	glCanvas->SwapBuffers(); 
//}