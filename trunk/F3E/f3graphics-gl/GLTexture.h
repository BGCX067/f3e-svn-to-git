#ifndef GLTEXTURE_H
#define GLTEXTURE_H

#include <f3graphics/ShaderResource.h>
#include <GL/glew.h>

namespace f3
{
	namespace graphics
	{
		class GLTexture : public ShaderResource
		{
			GLuint _data;

		public:
			GLTexture(void);
			~GLTexture(void);
			GLuint data();
			void setData(GLuint data);
		};
	}
}

#endif