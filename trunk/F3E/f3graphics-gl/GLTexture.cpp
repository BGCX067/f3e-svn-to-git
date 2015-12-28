
#include "GLTexture.h"

namespace f3
{
	namespace graphics
	{
		GLTexture::GLTexture(void)
		{
		}

		GLTexture::~GLTexture(void)
		{
		}

		void GLTexture::setData(GLuint data)
		{
			this->_data = data;
		}

		GLuint GLTexture::data()
		{
			return _data;
		}
	}
}