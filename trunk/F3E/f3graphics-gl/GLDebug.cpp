
#include "GLDebug.h"

GLDebug::GLDebug(void)
{
}


GLDebug::~GLDebug(void)
{
}

void GLDebug::init()
{
	typedef BOOL (APIENTRY *PFNWGLSWAPINTERVALFARPROC)( int );
	//typedef void (APIENTRY *TESTCALL)( void );
	PFNWGLSWAPINTERVALFARPROC opp = 0;
	PROC opp2 = 0;
	opp = (PFNWGLSWAPINTERVALFARPROC)wglGetProcAddress( "wglSwapIntervalEXT" );
	opp2 = wglGetProcAddress( "glGenFramebuffersEXT" );


	void* ptr = wglGetProcAddress("glDebugMessageCallback4");

	void* ptr3 = wglGetProcAddress("glBegin");
	if (glewIsExtensionSupported("GL_ARB_debug_output"))
	{
		f3u::log << "setting up opengl ARB debug output" << f3u::endl;
		setupArbDebugPrinter();
	}
	else if (glewIsExtensionSupported("GL_AMD_debug_output"))
	{
		f3u::log << "setting up opengl AMD debug output" << f3u::endl;
		setupAmdDebugPrinter();
	}
	else
	{
		f3u::log << "failed to setup opengl debug printer ARB/AMD" << f3u::endl;
	}


}

void GLDebug::setupArbDebugPrinter()
{
	glDebugMessageControlARB(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, NULL, true);
	//glDebugMessageCallbackARB(&arbCallback, NULL);
	glDebugMessageInsertARB(GL_DEBUG_SOURCE_APPLICATION_ARB, GL_DEBUG_TYPE_OTHER_ARB, 1, GL_DEBUG_SEVERITY_HIGH_ARB, 4, "test");
}

void GLDebug::setupAmdDebugPrinter()
{
	glDebugMessageEnableAMD(GL_DONT_CARE, GL_DONT_CARE, 0, NULL, true);
	glDebugMessageCallbackAMD(&amdCallback, NULL);
	glDebugMessageInsertAMD(GL_DEBUG_CATEGORY_APPLICATION_AMD, GL_DEBUG_SEVERITY_HIGH_AMD, 1, 4, "test");
}

void GLDebug::amdCallback(GLuint id,	GLenum category,	GLenum severity,	GLsizei length,	const GLchar* message,	GLvoid* userParam)
{
	f3u::log << id << " " << category << " " << severity << " l" << length << " msg:" << message << f3u::endl;
}
