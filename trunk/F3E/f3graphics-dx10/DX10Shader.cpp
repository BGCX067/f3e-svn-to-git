#include "DX10Shader.h"
#include <f3graphics/TextureLoader.h>
#include "DX10Texture.h"
#include <f3base/Common.h>
#include "DX10Device.h"

namespace f3
{
	namespace graphics
	{

		DX10Shader::DX10Shader(Device* device, std::string shadername) : Shader(device, shadername), _device((DX10Device*)device)
		{
			_pass = 0;
		}

		DX10Shader::~DX10Shader(void)
		{
		}

		f3::I32 DX10Shader::compile()
		{
			// Create the effect
			DWORD dwShaderFlags = D3D10_SHADER_ENABLE_STRICTNESS;

			#if defined( DEBUG ) || defined( _DEBUG )
			dwShaderFlags |= D3D10_SHADER_DEBUG;
			#endif

			HRESULT hr = NULL;
		
			std::string path = "resources/shader/hlsl/";
			std::string extension = ".hlsl";
					
			hr = D3DX10CreateEffectFromFile( (path+_name+extension).c_str(), NULL, NULL, "fx_4_0", dwShaderFlags, 0, _device->devicePtr(), NULL, NULL, &_effect, NULL, NULL);
			if( FAILED( hr ) )
			{
				f3u::log << f3u::log.WARNING << "Could not load HLSL file: " << (path+_name+extension).c_str() << "\n";
				return -1;
			}

			//Obtain the technique
			_technique = _effect->GetTechniqueByName( "Render" );
			_technique->GetDesc( &techDesc );
		
			// Define the input layout
			
			D3D10_INPUT_ELEMENT_DESC layout[] =
			{
				{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D10_INPUT_PER_VERTEX_DATA, 0 },
				{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 0, D3D10_INPUT_PER_VERTEX_DATA, 0 }
			};
			UINT numElements = sizeof(layout) / sizeof(layout[0]);

			// Create the input layout
			D3D10_PASS_DESC PassDesc;
			_technique->GetPassByIndex(0)->GetDesc(&PassDesc);
			hr = _device->devicePtr()->CreateInputLayout(layout, numElements, PassDesc.pIAInputSignature, PassDesc.IAInputSignatureSize, &_vertexlayout );
			if( FAILED( hr ) )
			{
				f3u::log.warning("failed to create input layout");
				return -1;
			}

			VertexLayoutDefinition def;
			def.insert(def.end(), VertexLayoutElement("POSITION", 0, 0, X32Y32Z32, sizeof(f3m::Vector2f)+sizeof(f3m::Vector3f), 0, PER_VERTEX));
			def.insert(def.end(), VertexLayoutElement("TEXCOORD", 0, 0, U32V32, sizeof(f3m::Vector2f)+sizeof(f3m::Vector3f), sizeof(f3m::Vector3f), PER_VERTEX));

			_device->createVertexLayout(&def, this, &this->_layout);
		
			// Set the input layout
			_device->devicePtr()->IASetInputLayout( _vertexlayout );
			_world = _effect->GetVariableByName( "World" )->AsMatrix();
			_view = _effect->GetVariableByName( "View" )->AsMatrix();
			_projection = _effect->GetVariableByName( "Projection" )->AsMatrix();
			_texture0 = _effect->GetVariableByName("texture0")->AsShaderResource();

			return 0;
		}

	
		void DX10Shader::setTexture(f3g::Texture* texture)
		{			
			_texture0->SetResource( ((DX10Texture*) texture->_shaderResource)->data );
		}

		ID3D10Effect* DX10Shader::effect()
		{
			return _effect;
		}

		void DX10Shader::begin()
		{
			_pass = 0;
		}

		int DX10Shader::currentPass()
		{
			return _pass;
		}

		void DX10Shader::startPass()
		{
			_technique->GetPassByIndex(_pass)->Apply( 0 );	
		}

		void DX10Shader::endPass()
		{
			_pass++;
		}

		int DX10Shader::passCount()
		{
			return techDesc.Passes;
		}

	
		void DX10Shader::setProjectionMatrix(f3m::Matrix4f& projection)
		{
			HRESULT rslt = _projection->SetMatrix((float*)&(projection));

			if (rslt == S_FALSE)
				f3u::log.info("failed to set projection matrix");
		}

		void DX10Shader::setViewMatrix(f3m::Matrix4f& view)
		{
			_view->SetMatrix((float*) &(view));
		}

		void DX10Shader::setWorldMatrix(f3m::Matrix4f& world)
		{
			_world->SetMatrix((float*) &(world));
		}

	}
}