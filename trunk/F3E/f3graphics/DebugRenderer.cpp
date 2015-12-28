
#include "DebugRenderer.h"
#include "Device.h"
#include "Shader.h"
#include "DebugContext.h"
#include "VertexLayout.h"

namespace f3
{
	namespace graphics
	{
		DebugRenderer::DebugRenderer(f3g::Device* device, DebugContext* context) :
			_device(device),
			_context(context), 
			lines(context->lines),
			points(context->points)
		{
			VertexLayoutDefinition def;
			def.insert(def.end(), VertexLayoutElement("POSITION", 0, 0, X32Y32Z32, sizeof(float)*3));


			_shader = device->getShaderLoader()->load("fallback");
			
			VertexLayout* layout = NULL;
			_device->createVertexLayout(&def, _shader, &layout);
			_vertexLayout = layout;

			BufferDescription desc;
			desc.size = sizeof(f3m::Vector3f) * 10000;

			_device->createBuffer(desc, NULL, &_buffer);
		}

		DebugRenderer::~DebugRenderer(void)
		{
			_device->releaseBuffer(_buffer);
			delete _buffer;
		}


		void DebugRenderer::render(MatrixSetup &matrices)
		{
			//Shader* prevShader = _device->currentShader();
			//_device->setShader(_shader);

			f3g::Shader* shader = _shader;//_device->currentShader();
			// draw lines
			if (lines.size() == 0)
				return;

			_device->updateBuffer( _buffer, (void*) &(lines[0]), sizeof(f3m::Vector3f) * lines.size() );
			_device->setBuffer(0, _buffer, 3*sizeof(float), 0);

			_device->setVertexLayout(_vertexLayout);
			_device->setRenderMode(Device::LINES);


			shader->begin();
			shader->setProjectionMatrix(matrices.projection);
			shader->setViewMatrix(matrices.view);
			shader->setWorldMatrix(matrices.world);

			while(shader->currentPass() < shader->passCount())
			{
				shader->startPass();
				_device->drawElements(lines.size());
				shader->endPass();
			}
			
			//_device->setShader(prevShader);
		}
	}
}