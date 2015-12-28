#ifndef GLMESHLOADER_H
#define GLMESHLOADER_H

#include "Mesh.h"

#include <windows.h>
#include <gl\glew.h>

class GLMeshLoader
{
public:
	GLMeshLoader(void);
	~GLMeshLoader(void);
	void load(f3::Mesh* mesh);
};

#endif