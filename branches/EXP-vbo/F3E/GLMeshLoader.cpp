#include "GLMeshLoader.h"
#include "Log.h"

GLMeshLoader::GLMeshLoader(void)
{
	glewInit();
}

GLMeshLoader::~GLMeshLoader(void)
{
}

void GLMeshLoader::load(f3::Mesh* mesh)
{
	unsigned int vb,ib;
	
	glGenBuffers(1, &vb);
	glBindBuffer(GL_ARRAY_BUFFER, vb);
	glBufferData(GL_ARRAY_BUFFER, mesh->_vertices.size()*sizeof(f3m::Vector3f), NULL, GL_STATIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(f3m::Vector3f) * mesh->_vertices.size(), &mesh->_vertices[0]);
	
	//glGenBuffers(1, &vb);
	//glBindBuffer(GL_ARRAY_BUFFER, vb);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(MyVertex)*3, &pvertex[0].x, GL_STATIC_DRAW);

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

	//mesh->ib = ib;
	mesh->vb = vb;

	//
	//GLenum erslt = glGetError();
	//
	//if (GL_NO_ERROR != erslt)
	//{
	//	char buffer[255];
	//	sprintf(buffer, "gl error: %s", gluErrorString(erslt));
	//	Log::getDefault()->write(Log::L_ERROR, buffer);
	//}
}