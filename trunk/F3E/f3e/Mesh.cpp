#include "Mesh.h"

namespace f3
{
	Mesh::Mesh(void) : shaderResource(NULL)
	{
		_texture = NULL;
		_device = NULL;
	}

	Mesh::~Mesh(void)
	{
	}

	f3::UI32 Mesh::vertexFormat()
	{
		return _vertexFormat;
	}
}