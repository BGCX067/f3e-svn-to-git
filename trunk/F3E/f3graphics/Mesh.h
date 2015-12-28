#ifndef MESH_H
#define MESH_H

#include <f3base/IDevice.h>
#include <f3math/Vector.h>
#include <vector>
#include <f3base/Common.h>
#include "Texture.h"
#include "ShaderResource.h"
#include "Buffer.h"
#include "VertexLayout.h"

namespace f3
{
	namespace graphics
	{


	class Mesh
	{
		
	protected:
		f3::graphics::IDevice* _device;

	public:
		f3g::VertexLayoutDefinition _vertexlayoutdef;
		std::vector<f3m::Vector2f> _texturecoordinates;
		std::vector<f3m::Vector3f> _vertices;
		std::vector<f3g::Index> _indices;
		f3g::Buffer* _buffer1;
		f3g::Buffer* _buffer2;
		f3g::Texture* _texture;

		Mesh(void);
		~Mesh(void);
	};


	}
}
#endif