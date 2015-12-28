#include "Texture.h"

namespace f3
{
	namespace graphics
	{
		Texture::Texture(std::string filename) : _shaderResource(NULL), _buffer(NULL), _size(0), _filename(filename)
		{
		}
		
		Texture::~Texture(void)
		{
			if (_buffer != NULL) 
				delete [] _buffer;
		}
	
		std::string Texture::filename()
		{
			return _filename;
		}

		char* Texture::buffer()
		{
			return _buffer;
		}

		long Texture::size()
		{
			return _size; 
		}
	}
}