#ifndef DX10Canvas_H
#define DX10Canvas_H

#include <Windows.h>
#include <f3graphics/Device.h>


#include <f3graphics/MeshLoader.h>
#include "DX10TextureLoader.h"
#include  <f3graphics/VertexLayoutElement.h>

struct ID3D10Device;
struct IDXGISwapChain;
struct ID3D10RenderTargetView;

namespace f3
{
	namespace graphics
	{
		class DX10VertexBuffer : public Buffer
		{
		public:
			DX10VertexBuffer() : Buffer() {};
			ID3D10Buffer* _buffer;
		};

		class DX10VertexLayout : public VertexLayout
		{
		public:
			DX10VertexLayout() : VertexLayout() {};
			ID3D10InputLayout* _vertexlayout;
		};
		
		class DX10Device : public Device
		{
			bool _fullscreen;
			HWND _hwnd;
			ID3D10Device* _device;
			IDXGISwapChain* _swapchain;
			ID3D10RenderTargetView* _rendertarget;
			
			D3D10_PRIMITIVE_TOPOLOGY _modes[3];

		private:
			void createRasterizerState();
			DXGI_SWAP_CHAIN_DESC swapchainSettings(bool fullscreen);

		protected:
			void present();
			void clear(f3u::ColorRGBA color);

		public:
			DX10Device(Window* window);
			~DX10Device(void);
			void init();
			void draw();
			void resize(int w, int h);
			void destroy();
			void setFullscreen(bool enabled);
			ID3D10Device* devicePtr();
			void drawElements( f3::I32 elements );
			void drawInstances(f3::I32 elements, f3::I32 instances);
			void setRenderMode( RenderMode mode );
			void setShader( Shader* shader );

			// Buffers
			void updateBuffer( Buffer* buffer, void* source, f3::I32 size);
			void createBuffer( BufferDescription desc, void* source, Buffer** target );
			void releaseBuffer( Buffer* buffer );
			void setBuffer( f3::I32 slot, f3g::Buffer* buffer, f3::UI32 stride, f3::UI32 offset );

			// vertexlayouts
			void createVertexLayout( VertexLayoutDefinition* definition, Shader* shader, VertexLayout** target );
			void releaseVertexLayout( VertexLayout* layout );
			void setVertexLayout( VertexLayout* layout );

		private:
			// helper
			D3D10_INPUT_CLASSIFICATION getInputSlotClass( VertexDataType type );
			DXGI_FORMAT getFormat( VertexFormat format );
		};
	}
}

#endif