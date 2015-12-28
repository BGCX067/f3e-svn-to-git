
#include "GLTextureLoader.h"
#include "GLTexture.h"
#include <f3base/Common.h>

namespace f3
{
	namespace graphics
	{

		GLTextureLoader::GLTextureLoader(void)
		{
		}

		GLTextureLoader::~GLTextureLoader(void)
		{
		}

		bool GLTextureLoader::load(Texture* texturedata)
		{
			TextureLoader::load(texturedata);
			
			GLuint texture;
			glGenTextures(1, &texture);
			
			// Typical Texture Generation Using Data From The Bitmap
			glBindTexture(GL_TEXTURE_2D, texture);

			glTexParameteri(GL_TEXTURE_2D, GL_GENERATE_MIPMAP, GL_TRUE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);	

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);	
			
			// Generate The Texture
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, texturedata->_description.width, texturedata->_description.height, 0, GL_RGBA, GL_UNSIGNED_BYTE, texturedata->buffer());
			
			GLTexture* gltexture = new GLTexture();
			gltexture->setData(texture);
			texturedata->_shaderResource = gltexture;

			return true;
		}

	}
}