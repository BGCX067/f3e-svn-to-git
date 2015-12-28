#ifndef DX10TEXTURELOADER_H
#define DX10TEXTURELOADER_H

#include <d3d10.h>
#include <D3DX10.h>
#include  <f3graphics/TextureLoader.h>
#include "DX10Texture.h"

namespace f3
{
	namespace graphics
	{
		class DX10Device;

		class DX10TextureLoader : public TextureLoader
		{
			DX10Device* _device;

		public:
			DX10TextureLoader(DX10Device* device);
			~DX10TextureLoader(void);
			bool load(f3r::Texture* texture);
		};
	}
}
#endif