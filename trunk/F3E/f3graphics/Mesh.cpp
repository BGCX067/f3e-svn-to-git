#include "Mesh.h"

namespace f3
{
	namespace graphics
	{
		Mesh::Mesh(void) :	_buffer1(NULL),
			_buffer2(NULL), 
			_texture(NULL), 
			_device(NULL)
		{
			_texture = NULL;
			_device = NULL;
		}

		Mesh::~Mesh(void)
		{
			delete _buffer1;
			delete _buffer2;
		}
	}
}