#include "DX10Device.h"
#include <iostream>
#include <f3base/Common.h>
#include <DXGI.h>
#include <f3math/Matrix.h>
#include <f3scene/Graph.h>
#include "DX10TextureLoader.h"
#include <f3scene/Node.h>
#include <f3math/Matrix.h>
#include "DX10Shader.h"
#include <f3base/Window.h>
#include <f3graphics-dx10/DX10Device.h>
#include <assert.h>
#include <f3graphics/ShaderLoader.h>

namespace f3
{
	namespace graphics
	{
		DX10Device::DX10Device(Window* window) : Device(window), _fullscreen(false)
		{
			f3::util::log.write("Creating DX10 Canvas");

			_width = 400;
			_height = 400;
			_swapchain = NULL;
			_device = NULL;
			_rendertarget = NULL;

			_modes[TRIANGLES] = D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
			_modes[POINTS] = D3D10_PRIMITIVE_TOPOLOGY_POINTLIST;
			_modes[LINES] = D3D10_PRIMITIVE_TOPOLOGY_LINELIST;
		}

		DX10Device::~DX10Device(void)
		{
			destroy();
		}

		void DX10Device::createRasterizerState()
		{
			ID3D10RasterizerState * rasterState;

			D3D10_RASTERIZER_DESC rsd;
			rsd.FillMode = D3D10_FILL_SOLID;// D3D10_FILL_WIREFRAME;
			rsd.CullMode = D3D10_CULL_NONE;
			rsd.FrontCounterClockwise = false;
			rsd.DepthBias = false;
			rsd.DepthBiasClamp = 0;
			rsd.SlopeScaledDepthBias = 0;
			rsd.DepthClipEnable = true;
			rsd.ScissorEnable = false;
			rsd.MultisampleEnable = true;
			rsd.AntialiasedLineEnable = true;
			_device->CreateRasterizerState( &rsd, &rasterState );
			_device->RSSetState(rasterState);
		}

		void DX10Device::draw()
		{
			if (_rendertarget == NULL)
				return;

			Device::draw();
		}

		void DX10Device::setShader( Shader* shader )
		{
			_shader = shader;
		}

		void DX10Device::clear( f3u::ColorRGBA color )
		{		    
			_device->ClearRenderTargetView(_rendertarget, (float*) &color);
		}

		void DX10Device::present()
		{
			//_swapchain->Present(1, 0); // VSYNC ON
			_swapchain->Present(0, 0);
		}
		
		void DX10Device::drawElements( f3::I32 elements )
		{
			_device->Draw( elements, 0 );
		}

		void DX10Device::drawInstances(f3::I32 elements, f3::I32 instances)
		{
			_device->DrawInstanced( elements, instances, 0, 0 );
		}

		void DX10Device::setRenderMode( RenderMode mode )
		{
			_device->IASetPrimitiveTopology(_modes[mode]);
		}

		DXGI_SWAP_CHAIN_DESC DX10Device::swapchainSettings(bool fullscreen)
		{
			DXGI_SWAP_CHAIN_DESC sd;
		    
			ZeroMemory( &sd, sizeof( sd ) );
			sd.BufferCount = 1;
			sd.BufferDesc.Width = _width;
			sd.BufferDesc.Height = _height;
			sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
			sd.BufferDesc.RefreshRate.Numerator = 59;
			sd.BufferDesc.RefreshRate.Denominator = 1;
			sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
			sd.OutputWindow = _hwnd;
			sd.SampleDesc.Count = 1;
			sd.SampleDesc.Quality = 0;
			sd.Windowed = !fullscreen;
			sd.SampleDesc.Count = 8;
			//sd.SampleDesc.Quality = 0;

			return sd;
		}

#pragma region buffers
		
		void DX10Device::setBuffer( f3::I32 slot, f3g::Buffer* buffer, f3::UI32 stride, f3::UI32 offset )
		{
			DX10VertexBuffer* vb = (DX10VertexBuffer*) buffer;

			_device->IASetVertexBuffers(slot, 1, &(vb->_buffer), &stride, &offset);
		}

		void DX10Device::createBuffer( f3g::BufferDescription desc, void* source, f3g::Buffer** target )
		{
			DX10VertexBuffer* vb = new DX10VertexBuffer();
			D3D10_BUFFER_DESC bd;
			bd.Usage = D3D10_USAGE_DYNAMIC;
			bd.ByteWidth = desc.size;
			bd.BindFlags = D3D10_BIND_VERTEX_BUFFER;
			bd.CPUAccessFlags = D3D10_CPU_ACCESS_WRITE;
			bd.MiscFlags = 0;

			// if no data is specified create an empty buffer
			if (source == NULL)
			{
				_device->CreateBuffer(&bd, NULL, &( vb->_buffer) );
			}
			// else create buffer and copy data
			else
			{
				D3D10_SUBRESOURCE_DATA data;
				data.pSysMem = source;
				_device->CreateBuffer(&bd, &data, &( vb->_buffer) );
			}

			*target = vb;
		}

		void DX10Device::releaseBuffer( f3g::Buffer* buffer )
		{
			DX10VertexBuffer* vb = (DX10VertexBuffer*) buffer;
			vb->_buffer->Release();
		}

		void DX10Device::updateBuffer( Buffer* buffer, void* source, f3::I32 size )
		{
			DX10VertexBuffer* vb = (DX10VertexBuffer*) buffer;
			void *pData = NULL;

			if( SUCCEEDED( vb->_buffer->Map( D3D10_MAP_WRITE_DISCARD, 0, reinterpret_cast< void** >( &pData ) ) ) )
			{
				memcpy( pData, source, size );
				vb->_buffer->Unmap( );
			}
		}

#pragma endregion buffers

		//*******************************
		//****** VERTEXLAYOUTS START ****
		//*******************************

		void DX10Device::setVertexLayout( VertexLayout* layout )
		{

		}
		
		void DX10Device::releaseVertexLayout( VertexLayout* layout )
		{

		}
		
		void DX10Device::createVertexLayout( VertexLayoutDefinition* definition, Shader* shader, VertexLayout** target )
		{
			DX10Shader* shad = (DX10Shader*) shader;
			DX10VertexLayout* layout = new DX10VertexLayout();
			
			layout->_definition = *definition;
			
			std::vector<D3D10_INPUT_ELEMENT_DESC> d3d_layout;

			f3g::VertexLayoutDefinition::iterator itr = definition->begin();

			while (itr != definition->end())
			{
				D3D10_INPUT_ELEMENT_DESC element;

				element.SemanticName = itr->_semenaticName.c_str();
				element.SemanticIndex = itr->_semanticSlot;
				element.Format = getFormat( (VertexFormat) itr->_format );
				element.InputSlot = itr->_bufferSlot;
				element.AlignedByteOffset = 0;
				element.InputSlotClass = getInputSlotClass( (VertexDataType) itr->_type );
				element.InstanceDataStepRate = 0;

				d3d_layout.push_back(element);				
				itr++;
			}
			//D3D10_INPUT_ELEMENT_DESC d3d_layout[] =
			//{
			//	{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D10_INPUT_PER_VERTEX_DATA, 0 },
			//	{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 1, 0, D3D10_INPUT_PER_VERTEX_DATA, 0 }
			//};
			//UINT numElements = sizeof(layout) / sizeof(layout[0]);

			//// Create the input layout
			D3D10_PASS_DESC PassDesc;

			shad->_technique->GetPassByIndex(0)->GetDesc(&PassDesc);
			devicePtr()->CreateInputLayout(&(d3d_layout[0]), d3d_layout.size(), PassDesc.pIAInputSignature, PassDesc.IAInputSignatureSize, &layout->_vertexlayout );

			(*target) = layout;
		}

		D3D10_INPUT_CLASSIFICATION DX10Device::getInputSlotClass(VertexDataType type)
		{
			if (type == PER_INSTANCE)
				return D3D10_INPUT_PER_INSTANCE_DATA;

			if (type == PER_VERTEX)
				return D3D10_INPUT_PER_VERTEX_DATA;

			assert(true);

			return D3D10_INPUT_PER_VERTEX_DATA;
		}

		DXGI_FORMAT DX10Device::getFormat( VertexFormat format )
		{
			if (format == X32Y32Z32)
				return DXGI_FORMAT_R32G32B32_FLOAT;

			if (format == U32V32)
				return DXGI_FORMAT_R32G32_FLOAT;

			assert(true);

			return DXGI_FORMAT_R32G32B32_FLOAT;
		}

		//*****************************
		//****** VERTEXLAYOUTS END ****
		//*****************************
		
		void DX10Device::init()
		{
			_hwnd = _window->handle();
			unsigned int flags = 0;
			//flags |= D3D10_CREATE_DEVICE_DEBUG;
			
			DXGI_SWAP_CHAIN_DESC sd = swapchainSettings(_fullscreen);

			HRESULT hr;
			hr = D3D10CreateDeviceAndSwapChain(NULL, D3D10_DRIVER_TYPE_HARDWARE, NULL, flags, D3D10_SDK_VERSION, &sd, &_swapchain, &_device);
			//hr = D3D10CreateDeviceAndSwapChain(NULL, D3D10_DRIVER_TYPE_NULL, NULL, flags, D3D10_SDK_VERSION, &sd, &_swapchain, &_device);

			if (hr != S_OK)
			{
				std::cout << hr;
				throw new std::exception("failed to create device and/or swapchain");
			}
			
			_textureloader = new f3r::DX10TextureLoader(this);
			//_shaderloader = new f3r::DX10ShaderLoader(this);
			_shaderloader = new f3r::ShaderLoader<DX10Device, DX10Shader>(this);

			ID3D10Texture2D* backbuffer;
		    
			_swapchain->GetBuffer( 0, __uuidof(ID3D10Texture2D), (LPVOID*)&backbuffer);
			_device->CreateRenderTargetView(backbuffer, NULL, &_rendertarget);
			_device->OMSetRenderTargets( 1, &_rendertarget, NULL );

			backbuffer->Release();
		    

			createRasterizerState();
			Device::init();
		}

		void DX10Device::setFullscreen(bool enabled)
		{
			if (enabled == false)
			{
				//std::cout << "FALSE";
			}
			if (_swapchain != NULL)
			{
				if (enabled)
				{
					resize(1920,1200);
				
					IDXGIOutput* out;
					_swapchain->GetContainingOutput(&out);
					_swapchain->SetFullscreenState(enabled, out);
				}
				else
				{
					resize(800,600);
					_swapchain->SetFullscreenState(false, NULL);
				}
			}
			_fullscreen = enabled;
		}

		void DX10Device::destroy()
		{
			if (_fullscreen)
				_swapchain->SetFullscreenState(false, NULL);

			_device->ClearState();
			_rendertarget->Release();
			_swapchain->Release();
			_device->Release();
		}

		void DX10Device::resize(int width, int height)		// Resize And Initialize The GL Window
		{
			IDXGIOutput* output = NULL;

			_width = width;
			_height = height;

			//_device->ClearState();
			_rendertarget->Release();
			_rendertarget = NULL;

			HRESULT hr = _swapchain->ResizeBuffers(1, width, height, DXGI_FORMAT_R8G8B8A8_UNORM, DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH);

			if (FAILED(hr))
				return;

			ID3D10Texture2D* backbuffer = NULL;
			_swapchain->GetBuffer(0, __uuidof(ID3D10Texture2D), (LPVOID*)&backbuffer);
			_device->CreateRenderTargetView(backbuffer, NULL, &_rendertarget);
			_device->OMSetRenderTargets( 1, &_rendertarget, NULL );

			backbuffer->Release();

			D3D10_VIEWPORT viewport;
			viewport.Width = width;
			viewport.Height = height;
			viewport.MinDepth = 0.0f;
			viewport.MaxDepth = 1.0f;
			viewport.TopLeftX = 0;
			viewport.TopLeftY = 0;
			_device->RSSetViewports(1, &viewport);
		}
		
		ID3D10Device* DX10Device::devicePtr()
		{
			return _device;
		}

		
	}
}