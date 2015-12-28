#ifndef GLDebug_h__
#define GLDebug_h__

#include "F3GL.h"

#include <f3base/Common.h>
#include <f3base/Log.h>

class GLDebug
{
public:
	GLDebug(void);
	~GLDebug(void);
	void init();
	void setupArbDebugPrinter();
	void setupAmdDebugPrinter();
	static void CALLBACK  amdCallback(GLuint id, GLenum category, GLenum severity, GLsizei length, const GLchar* message, GLvoid* userParam);
};

#endif // GLDebug_h__
