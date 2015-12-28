#ifndef ITEXTURELOADER_H
#define ITEXTURELOADER_H

#include "Common.h"

namespace f3
{
	namespace graphics 
	{
		class Texture;
		class TextureDescription;

		class ITextureLoader
		{
		public:
			virtual bool load(Texture* texture) = 0;
		};
	}
}
#endif