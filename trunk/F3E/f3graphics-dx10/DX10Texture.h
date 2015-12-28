#ifndef DX10TEXTURE_H
#define DX10TEXTURE_H

#include  <f3graphics/ShaderResource.h>
#include <d3d10.h>
#include <d3dx10.h>

namespace f3
{
	namespace graphics
	{
		class DX10Texture : public ShaderResource
		{
		public:
			ID3D10ShaderResourceView* data;
			DX10Texture(void);
			~DX10Texture(void);
		};
	}
}

#endif