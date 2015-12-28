
#include "DX10TextureLoader.h"
#include "DX10Device.h"

namespace f3
{
	namespace graphics
	{

		DX10TextureLoader::DX10TextureLoader(DX10Device* device)
		{
			_device = device;
		}

		DX10TextureLoader::~DX10TextureLoader(void)
		{
		}

		bool DX10TextureLoader::load(Texture* rawtexture)
		{
			TextureLoader::load(rawtexture);

			D3D10_SUBRESOURCE_DATA data;
			data.pSysMem = rawtexture->buffer();
			data.SysMemPitch = 4 * rawtexture->_description.width; // bytes per row
			data.SysMemSlicePitch = 0;
			
			ID3D10Texture2D* Texture;

			D3D10_TEXTURE2D_DESC textureDesc;
			ZeroMemory( &textureDesc, sizeof( textureDesc ) );
			textureDesc.Width = rawtexture->_description.width;
			textureDesc.Height = rawtexture->_description.height;
			textureDesc.MipLevels = 0;
			textureDesc.ArraySize = 1;
			textureDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM_SRGB;
			textureDesc.SampleDesc.Count = 1;
			textureDesc.SampleDesc.Quality = 0;
			textureDesc.Usage = D3D10_USAGE_DEFAULT;
			textureDesc.BindFlags = D3D10_BIND_SHADER_RESOURCE |   D3D10_BIND_RENDER_TARGET;
			textureDesc.CPUAccessFlags = 0;
			textureDesc.MiscFlags = D3D10_RESOURCE_MISC_GENERATE_MIPS;

			_device->devicePtr()->CreateTexture2D( &textureDesc, NULL, &Texture );

			D3D10_SHADER_RESOURCE_VIEW_DESC srvDesc;
			srvDesc.Format = textureDesc.Format;
			srvDesc.ViewDimension = D3D10_SRV_DIMENSION_TEXTURE2D;
			srvDesc.Texture2D.MostDetailedMip = 0;
			srvDesc.Texture2D.MipLevels = 8;

			_device->devicePtr()->UpdateSubresource(Texture,0, NULL, rawtexture->buffer(), rawtexture->_description.width*4, rawtexture->_description.height*rawtexture->_description.width*4);

			ID3D10ShaderResourceView *srvTexture = NULL;
			_device->devicePtr()->CreateShaderResourceView( Texture, &srvDesc, &srvTexture );

			_device->devicePtr()->GenerateMips(srvTexture);

			Texture->Release();

			f3r::DX10Texture* tex = new f3r::DX10Texture();
			tex->data = srvTexture;
			rawtexture->_shaderResource = tex;

			return true;
		}
	}
}