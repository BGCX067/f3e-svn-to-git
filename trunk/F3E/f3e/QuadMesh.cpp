#include "QuadMesh.h"


namespace f3
{
	QuadMesh::QuadMesh() : Mesh()
	{
		_vertices.clear();

		_vertexFormat = VertexFormat::POSITION | VertexFormat::TEXCOORD1;

		_vertices.insert(_vertices.end(), f3m::Vector3f(-0.5f, -0.5f, 0.0f));
		_vertices.insert(_vertices.end(), f3m::Vector3f(-0.5f, 0.5f, 0.0f));
		_vertices.insert(_vertices.end(), f3m::Vector3f(0.5f, -0.5f, 0.0f));

		_vertices.insert(_vertices.end(), f3m::Vector3f(0.5f, -0.5f, 0.0f));
		_vertices.insert(_vertices.end(), f3m::Vector3f(0.5f, 0.5f, 0.0f));
		_vertices.insert(_vertices.end(), f3m::Vector3f(-0.5f, 0.5f, 0.0f));

		_texturecoordinates.insert(_texturecoordinates.end(), f3m::Vector2f(0,0));
		_texturecoordinates.insert(_texturecoordinates.end(), f3m::Vector2f(0,1));
		_texturecoordinates.insert(_texturecoordinates.end(), f3m::Vector2f(1,0)); 

		_texturecoordinates.insert(_texturecoordinates.end(), f3m::Vector2f(1,0));
		_texturecoordinates.insert(_texturecoordinates.end(), f3m::Vector2f(1,1));
		_texturecoordinates.insert(_texturecoordinates.end(), f3m::Vector2f(0,1)); 

		//if (i == 1)
		//else
		//_texture = new f3r::Texture("resources/textures/test3_RGBA_8b_128.raw");
		//f3r::Texture::Description texdesc;
		//texdesc.format = f3r::Texture::Format::R8G8B8A8;
		//texdesc.width = 128;
		//texdesc.height = 128;
		//_texture->desc = texdesc;
	}

	QuadMesh::~QuadMesh(void)
	{
	}
}