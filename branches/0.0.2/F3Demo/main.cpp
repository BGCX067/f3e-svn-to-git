#define CASE1

#ifdef CASE1
//#define EXPORTDLL
#include "F3ECommandManager.h"
#include <iostream>
#include "F3EMain.h"
//
//class Test : public F3EICommandListener
//{
//public:
//	void execute(F3EICommand* c)
//	{
//		std::cout << "cmd: " << c->getCommandString() << std::endl;
//	};
//};
//
class App : public F3EIApplication
{
	void OnInit() { std::cout << "init" <<std::endl; };
	void OnUpdate() {};
	void OnExit() {};
};

void main()
{
	std::string query;
	std::stringbuf buffer;

	start(new App());

	//F3ECommandManager cm;
	//
	//F3ECommand* command1 = new F3ECommand("sv_servername");
	//command1->addParameter(new F3ECommandVarBool("shouldbebool","a 255 character long servername"));
	//command1->addParameter(new F3ECommandVarInt("shouldbeint","numeric value 0-8000"));

	//F3ECommand* command2 = new F3ECommand("exit");
	//
	//Test t;
	//cm.addListener(&t);
	//cm.add(command1);
	//cm.add(command2);

	//std::cout << command1->getDesc();
	//
	//while (0==0)
	//{
	//	try 
	//	{
	//		//cm.submit("sv_servername true -1");
	//		//std::cin >> inputstr;
	//		query = "";
	//		std::cout << "> ";// Type something with spaces here. e.g ( "financial instruments being traded on the American stock exchange" );
	//
	//		std::getline(std::cin,query);
	//		cm.submit(query);
	//	}
	//	catch (std::exception e)
	//	{
	//		std::cout << e.what() << std::endl;
	//		system("PAUSE");
	//		return;
	//	}

	//
	////COORD co = {width,height};
	////SetConsoleScreenBufferSize(__hStdOut, co);

	//	//WindowUpdate();
	//}

	return;
}
#endif
#ifdef CASE2

#include "wx/wx.h"

#include "main.h"
 
IMPLEMENT_APP(HelloWorldApp)
 
// This is executed upon startup, like 'main()' in non-wxWidgets programs.
bool HelloWorldApp::OnInit()
{
	wxFrame *frame = new wxFrame((wxFrame*) NULL, -1, _T("Hello wxWidgets World"));
	frame->CreateStatusBar();
	frame->SetStatusText(_T("Hello World"));
	frame->Show(true);
	SetTopWindow(frame);
	return true;
}
#endif

#ifdef CASE3
#include "wx/wx.h" 
#include "wx/glcanvas.h" 

#ifndef WIN32 
#include <unistd.h> 
#endif 

class MyApp: public wxApp 
{ 
  virtual bool OnInit(); 
}; 

int attrib[2]; 



IMPLEMENT_APP(MyApp) 

bool MyApp::OnInit() 
{ 
        attrib[0] = WX_GL_DEPTH_SIZE; 
        attrib[1] = 32; 
  wxFrame *frame = new wxFrame((wxFrame *)NULL, -1,  "Hello GL World", wxPoint(50,50), wxSize(450,450) ); 
  wxGLCanvas * MyGLCanvas = new wxGLCanvas(frame, -1, wxPoint(0,0), wxSize(400,400), wxSUNKEN_BORDER, _("some text")); 

  frame->Show(TRUE); 

  MyGLCanvas->SetCurrent(); 
  //sleep(1); 
  //..or try this instead 
  glClearColor(0.0, 0.0, 0.0, 0.0); 
  glClear(GL_COLOR_BUFFER_BIT); 
  glViewport(50, 50, (GLint)100, (GLint)100); 
  glLoadIdentity(); 
  glTranslatef(0.0f,1.0f,0.0f); 

  glColor3f(1.0, 1.0, 1.0); 

  glBegin(GL_TRIANGLES); 
        glColor3f(1.0f,0.0f,0.0f);                        // Set The Color To Red 
        glVertex3f( 0.0f, 1.0f, 0.0f);                        // Move Up One Unit From Center (Top Point) 
        glColor3f(0.0f,1.0f,0.0f);                        // Set The Color To Green 
        glVertex3f(-1.0f,-1.0f, 0.0f);                        // Left And Down One Unit (Bottom Left) 
    glColor3f(0.0f,0.0f,1.0f);                        // Set The Color To Blue 
        glVertex3f( 1.0f,-1.0f, 0.0f);                        // Right And Down One Unit (Bottom Right) 
  glEnd();                                                // Done Drawing A Triangle 

//  glTranslatef(1.5f,0.0f,0.0f);                                // From Right Point Move 3 Units Right 
  
/*  glBegin(GL_QUADS); 
                glVertex3f(-1.0f, 1.0f, 0.0f);                        // Left And Up 1 Unit (Top Left) 
                glVertex3f( 1.0f, 1.0f, 0.0f);                        // Right And Up 1 Unit (Top Right) 
                glVertex3f( 1.0f,-1.0f, 0.0f);                        // Right And Down One Unit (Bottom Right) 
                glVertex3f(-1.0f,-1.0f, 0.0f);                        // Left And Down One Unit (Bottom Left) 

  glEnd();*/ 
  glFlush(); 

  MyGLCanvas->SwapBuffers(); 
  return TRUE; 
} 
#endif