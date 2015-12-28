#ifndef MESH_H
#define MESH_H

#include <f3base/IDevice.h>
#include <f3math/Vector.h>
#include <vector>
#include <f3base/Common.h>
#include "Texture.h"
#include "ShaderResource.h"

namespace f3
{
	typedef unsigned short Index;

	class DLL Mesh
	{
	public:
		enum VertexFormat { POSITION = 1, TEXCOORD1 = 2, TEXCOORD2 = 4};
		
	protected:
		f3::UI32 _vertexFormat;
		f3::graphics::IDevice* _device;

	public:
		std::vector<f3m::Vector2f> _texturecoordinates;
		std::vector<f3m::Vector3f> _vertices;
		std::vector<f3::Index> _indices;

		f3g::Texture* _texture;

		Mesh(void);
		~Mesh(void);
		f3::UI32 Mesh::vertexFormat();


		ShaderResource* shaderResource;
	};
}
#endif