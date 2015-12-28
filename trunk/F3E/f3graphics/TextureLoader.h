#ifndef TEXTURELOADER_H
#define TEXTURELOADER_H
#include <f3base/Common.h>

#include "Texture.h"
#include <string>
#include <map>
#include <f3base/ITextureLoader.h>

namespace f3
{
	namespace graphics
	{

		class TextureLoader : public ITextureLoader
		{
		protected:
			int _mipmaplevels;
			std::map<std::string, f3g::Texture*> textures;

		public:
			TextureLoader(void);
			virtual ~TextureLoader(void);
			virtual bool load(Texture* texture);
			bool TextureLoader::loadRaw(Texture* texture);
		};
	}
}

#endif