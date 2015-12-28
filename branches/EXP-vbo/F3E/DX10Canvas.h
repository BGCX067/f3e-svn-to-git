#ifndef dx10canvas_H
#define dx10canvas_H

#include <windows.h>
#include <d3d10.h>
#include <d3dx10.h>
#include "ICanvas.h"
#include "DX10MeshLoader.h"

namespace graphics
{
	class dx10canvas : public ICanvas
	{
		int _width;
		int _height;
		bool _fullscreen;

		HWND _hwnd;
		ID3D10Device* _device;
		IDXGISwapChain* _swapchain;
		ID3D10RenderTargetView* _rendertarget;
		DX10MeshLoader* loader;
		ID3D10Effect* _effect;
		ID3D10EffectTechnique* _technique;
		ID3D10InputLayout* _vertexlayout;

	public:
		dx10canvas(void);
		~dx10canvas(void);
		void init(HWND hwnd);
		void draw();
		void resize(int w, int h);
		void destroy();
		void setFullscreen(bool enabled);
		DXGI_SWAP_CHAIN_DESC swapchainSettings(bool fullscreen);
	};
}

#endif