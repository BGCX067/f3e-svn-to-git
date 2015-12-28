#ifndef GLTEXTURELOADER_H
#define GLTEXTURELOADER_H

#include <f3graphics/TextureLoader.h>

namespace f3
{
	namespace graphics
	{
		class GLTextureLoader : public TextureLoader
		{
		public:
			GLTextureLoader(void);
			~GLTextureLoader(void);
			bool load(f3r::Texture* texture);
		};
	}
}
#endif