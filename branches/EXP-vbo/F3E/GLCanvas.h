#ifndef GLCanvas_H
#define GLCanvas_H

#ifdef WIN32
#include <windows.h>
#endif

#include <gl\glew.h>
#include "ICanvas.h"
#include "Mesh.h"
#include "Node.h"

struct MyVertex
	{
		float x, y, z;
	};
namespace graphics
{
	class GLCanvas : public ICanvas
	{
		unsigned int vb,ib;
		int _width;
		int _height;
		f3::Mesh _mesh;
		MyVertex pvertex[3];
	
	public:
		GLCanvas(void);
		~GLCanvas(void);
		void init();
		void draw();
		void destroy();
		void resize(int w, int h);
		void drawNode(f3::Node* node);
	};
}

#endif