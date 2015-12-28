#ifndef DX10SHADER_H
#define DX10SHADER_H

#include <f3graphics/Shader.h>
#include <d3d10.h>
#include <d3dx10.h>
#include <f3math/Matrix.h>
#include "DX10Texture.h"
#include <f3base/Common.h>

namespace f3
{
	namespace graphics
	{
		class DX10Device;

		class DX10Shader : public Shader
		{
			ID3D10Effect* _effect;
			DX10Device* _device;
			ID3D10InputLayout* _vertexlayout;
			D3D10_TECHNIQUE_DESC techDesc;
			int _pass;

			ID3D10EffectMatrixVariable* _world;
			ID3D10EffectMatrixVariable* _view;
			ID3D10EffectShaderResourceVariable* _texture0;
			ID3D10EffectMatrixVariable* _projection;

		public:
			DX10Shader(Device* device, std::string shadername);
			~DX10Shader(void);
			ID3D10EffectTechnique* _technique;

			void setDevice(DX10Device* device);
			f3::I32 compile();
			bool processing();
			void begin();
			int currentPass();
			int passCount();
			void startPass();
			void endPass();
			void setProjectionMatrix(f3m::Matrix4f& matrix);
			void setViewMatrix(f3m::Matrix4f& matrix);
			void setWorldMatrix(f3m::Matrix4f& matrix);
			ID3D10Effect* effect();
			void DX10Shader::setTexture(f3g::Texture* texture);
		};
	}
}
#endif