#include "GLCanvas.h"
#include "Common.h"
#include "GLMeshLoader.h"
#include "Scene.h"

namespace graphics
{

GLCanvas::GLCanvas(void)
{
	Log::getDefault()->write("Creating OpenGL Canvas");
	
	_mesh._vertices.insert(_mesh._vertices.end(), f3m::Vector3f(0.0f, 0.98f, 0.0f));
	_mesh._vertices.insert(_mesh._vertices.end(),f3m::Vector3f(0.55f, -0.55f, 0.0f));
	_mesh._vertices.insert(_mesh._vertices.end(),f3m::Vector3f(-0.55f, -0.55f, 0.0f));
	GLMeshLoader loader;
	loader.load(&_mesh);
}

GLCanvas::~GLCanvas(void)
{
	glDeleteBuffers(1, &vb);
}

void GLCanvas::draw()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	//glViewport(0, 0, _width, _height);
	glTranslatef(0.0f,0.0f,-2.4f);


	//glBegin(GL_LINE_LOOP);		
	//	glVertex3f( 0.0f, 1.1f, 0.0f);
	//	glVertex3f(-1.1f,-1.1f, 0.0f);
	//	glVertex3f( 1.0f,-1.0f, 0.0f);
	//glEnd();

	//unsigned short pindices[3];
	//pindices[0] = 0;
	//pindices[1] = 1;
	//pindices[2] = 2;

	//glGenBuffers(1, &ib);
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ib);
	//glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned short)*3, pindices, GL_STATIC_DRAW);

	//	glBindBuffer(GL_ARRAY_BUFFER, vb);
	//glEnableVertexAttribArray(0);    //We like submitting vertices on stream 0 for no special reason
	//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(MyVertex), 0);   //The
//	glDisableClientState(NULL);
//	glEnableClientState(GL_VERTEX_ARRAY);
//	
//	glBindBuffer( GL_ARRAY_BUFFER, vb);
//	//glVertexPointer( 3, GL_FLOAT, 1, (char *) NULL );
//	
//	glVertexPointer(3, GL_FLOAT, sizeof(float)*3, NULL );
//	
//
//	//glDrawElements(GL_LINES, 2, GL_FLOAT, 0);
//	glDrawArrays( GL_POINTS, 0, 3);
//glDisableClientState( GL_VERTEX_ARRAY );				// Disable Vertex Arrays
//	
//float* ptr = (float*)glMapBuffer(GL_ARRAY_BUFFER, GL_READ_ONLY);
//
//std::cout << ptr[0] << std::endl;

	//glTranslatef(3.0f,0.0f,0.0f);
	//glBegin(GL_LINE_LOOP);
	//	glVertex3f(-1.0f, 1.0f, 0.0f);
	//	glVertex3f( 1.0f, 1.0f, 0.0f);
	//	glVertex3f( 1.0f,-1.0f, 0.0f);
	//	glVertex3f(-1.0f,-1.1f, 0.0f);
	//glEnd();

	#define BUFFER_OFFSET(i) ((char *)NULL + (i))

	
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(50.0, 1.0, f3::Scene::getDefault()->camera()->nearPlane(),  f3::Scene::getDefault()->camera()->farPlane()); 
	glMatrixMode(GL_MODELVIEW); 
	glLoadIdentity(); 

	f3m::Vector3f cp = f3::Scene::getDefault()->camera()->position();
	f3m::Vector3f ct = f3::Scene::getDefault()->camera()->target();
	
	gluLookAt(cp[0], cp[1], cp[2],
		ct[0], ct[1], ct[2], 
		0.0, 1.0, 0.0);

	drawNode(f3::Scene::getDefault()->root());

	// Post Last OpenGL Error
	GLenum erslt = glGetError();
	
	if (GL_NO_ERROR != erslt)
	{
		char buffer[255];
		sprintf(buffer, "OpenGL Error: %s", gluErrorString(erslt));
		Log::getDefault()->write(Log::L_ERROR, buffer);
	}
}

void GLCanvas::destroy()
{
}

void GLCanvas::drawNode(f3::Node* node)
{
	glPushMatrix(); 
	glTranslatef(node->position()[0], node->position()[1], node->position()[2]);

	glBindBuffer(GL_ARRAY_BUFFER, _mesh.vb);
	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_FLOAT, sizeof(f3m::Vector3f), BUFFER_OFFSET(0));
	glDrawArrays(GL_LINE_LOOP, 0, _mesh._vertices.size());
    glDisableClientState(GL_VERTEX_ARRAY); 
		
	glPopMatrix();

	//Log::getDefault()->write(node->toString());

	if (!node->hasChildren())
		return;

	f3::NodeList* nl = node->children();
	f3::NodeList::iterator itr = nl->begin();

	while (itr != nl->end())
	{
		drawNode((*itr));
		itr++;
	}
}

void GLCanvas::init()
{
	glShadeModel(GL_SMOOTH);
	glClearColor(0.25f, 0.25f, 0.25f, 0.0f);
	glClearDepth(1.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

	char buffer[255];
	sprintf(buffer, "OpenGL Version: %s - GLU Version: %s", glGetString(GL_VERSION), gluGetString(GLU_VERSION));
	Log::getDefault()->write(buffer);
}

void GLCanvas::resize(int width, int height)		// Resize And Initialize The GL Window
{
	_width = width;
	_height = height;

	if (height==0)										// Prevent A Divide By Zero By
		height=1;										

	glViewport(0,0,_width,_height);						// Reset The Current Viewport

	glMatrixMode(GL_PROJECTION);						// Select The Projection Matrix
	glLoadIdentity();									// Reset The Projection Matrix

	// Calculate The Aspect Ratio Of The Window
	gluPerspective(45.0f,(GLfloat)width/(GLfloat)height,0.1f,100.0f);

	glMatrixMode(GL_MODELVIEW);							// Select The Modelview Matrix
	glLoadIdentity();									// Reset The Modelview Matrix
}

}