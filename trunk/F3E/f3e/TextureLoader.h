#ifndef TEXTURELOADER_H
#define TEXTURELOADER_H

#include "Texture.h"
#include <string>
#include <gl\glew.h>
#include <map>
#include <f3base\ITextureLoader.h>

namespace f3
{
	namespace graphics
	{

		class TextureLoader : public ITextureLoader
		{
		protected:
			int _mipmaplevels;
			std::map<std::string, f3r::Texture*> textures;
			TextureLoader(void);

		public:
			~TextureLoader(void);

			//virtual void setMipMapLevels(int levels);
			virtual bool load(Texture* texture);
			//Texture* load(std::string filename);
			//Texture* loadRaw(std::string filename, TextureDescription& texdesc);
			//Texture* loadDummy();
		};
	}
}

namespace f3r = f3::graphics;
#endif