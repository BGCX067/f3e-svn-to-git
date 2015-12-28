#ifndef ICANVAS_H
#define ICANVAS_H

#include "IMeshLoader.h"
#include "ITextureLoader.h"
#include "IShaderLoader.h"

namespace f3
{
	namespace graphics
	{
		class IDevice
		{
			enum TextureSlot { DIFFUSE, NORMAL, ALPHA };

		public:
			virtual void draw() = 0;
			virtual void destroy() = 0;
			virtual void resize(int w, int h) = 0;
			virtual f3r::IMeshLoader* getMeshLoader() = 0;
			virtual f3r::ITextureLoader* getTextureLoader() = 0;
			virtual f3r::IShaderLoader* getShaderLoader() = 0;
			virtual void setTexture(f3r::Texture* texture) = 0;
		};
	}
}
#endif