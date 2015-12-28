#include "dx10canvas.h"
#include <iostream>
#include "Common.h"
#include <DXGI.h>

namespace graphics
{

dx10canvas::dx10canvas(void)
{
	Log::getDefault()->write("Creating DX10 Canvas");

	_width = 400;
	_height = 400;
	_swapchain = NULL;
	_device = NULL;
	_rendertarget = NULL;
	
}

dx10canvas::~dx10canvas(void)
{
	destroy();
}

void dx10canvas::draw()
{
	if (_rendertarget == NULL)
		return;

    float clearcolor[4] = { 0.65f, 0.25f, 0.25f, 1.0f };
    _device->ClearRenderTargetView(_rendertarget, clearcolor);

	
	// Render a triangle
    D3D10_TECHNIQUE_DESC techDesc;
    _technique->GetDesc( &techDesc );
    for( UINT p = 0; p < techDesc.Passes; ++p )
    {
        _technique->GetPassByIndex( p )->Apply( 0 );
        _device->Draw(6, 0 );
    }

    _swapchain->Present(0, 0);
}

DXGI_SWAP_CHAIN_DESC dx10canvas::swapchainSettings(bool fullscreen)
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

	return sd;
}

void dx10canvas::init(HWND hwnd)
{
	_hwnd = hwnd;
	unsigned int flags = 0;
    //flags |= D3D10_CREATE_DEVICE_DEBUG;
	
	DXGI_SWAP_CHAIN_DESC sd = swapchainSettings(_fullscreen);

	HRESULT hr;
	if (S_OK != D3D10CreateDeviceAndSwapChain(NULL, D3D10_DRIVER_TYPE_HARDWARE, NULL, flags, D3D10_SDK_VERSION, &sd, &_swapchain, &_device))
		throw new std::exception("failed to create device and/or swapchain");
	
	ID3D10Texture2D* backbuffer;
    
	_swapchain->GetBuffer( 0, __uuidof(ID3D10Texture2D), (LPVOID*)&backbuffer);
    _device->CreateRenderTargetView(backbuffer, NULL, &_rendertarget);
	_device->OMSetRenderTargets( 1, &_rendertarget, NULL );

	backbuffer->Release();
    

	 // Create the effect
    DWORD dwShaderFlags = D3D10_SHADER_ENABLE_STRICTNESS;
#if defined( DEBUG ) || defined( _DEBUG )
    // Set the D3D10_SHADER_DEBUG flag to embed debug information in the shaders.
    // Setting this flag improves the shader debugging experience, but still allows 
    // the shaders to be optimized and to run exactly the way they will run in 
    // the release configuration of this program.
    dwShaderFlags |= D3D10_SHADER_DEBUG;
    #endif
    
	hr = D3DX10CreateEffectFromFile("effect.fx", NULL, NULL, "fx_4_0", dwShaderFlags, 0, _device, NULL, NULL, &_effect, NULL, NULL);
	if( FAILED( hr ) )
    {
        MessageBox(NULL, "The FX file cannot be located.  Please run this executable from the directory that contains the FX file.", "Error", MB_OK);
        return;
    }

     //Obtain the technique
    _technique = _effect->GetTechniqueByName( "Render" );

    // Define the input layout
    D3D10_INPUT_ELEMENT_DESC layout[] =
    {
        { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D10_INPUT_PER_VERTEX_DATA, 0 },
    };
    UINT numElements = sizeof(layout) / sizeof(layout[0]);

    // Create the input layout
    D3D10_PASS_DESC PassDesc;
    _technique->GetPassByIndex(0)->GetDesc(&PassDesc);
    hr = _device->CreateInputLayout( layout, numElements, PassDesc.pIAInputSignature, PassDesc.IAInputSignatureSize, &_vertexlayout );
    if( FAILED( hr ) )
        return;

    // Set the input layout
    _device->IASetInputLayout( _vertexlayout );

    // Obtain the technique
    _technique = _effect->GetTechniqueByName( "Render" );


    // Setup the viewport
    D3D10_VIEWPORT vp;
    vp.Width = _width;
    vp.Height = _height;
    vp.MinDepth = 0.0f;
    vp.MaxDepth = 10.0f;
    vp.TopLeftX = 0;
    vp.TopLeftY = 0;
    _device->RSSetViewports( 1, &vp );

	loader = new DX10MeshLoader(_device);
	loader->load(NULL);
}

void dx10canvas::setFullscreen(bool enabled)
{
	if (enabled == false)
	{
		std::cout << "FALSE";
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

void dx10canvas::destroy()
{
	if (_fullscreen)
		_swapchain->SetFullscreenState(false, NULL);

	_device->ClearState();
    _rendertarget->Release();
    _swapchain->Release();
    _device->Release();
}

void dx10canvas::resize(int width, int height)		// Resize And Initialize The GL Window
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


}