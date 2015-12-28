#include "MeshLoader.h"
#include "Device.h"
#include "Mesh.h"

namespace f3
{
	namespace graphics
	{
		MeshLoader::MeshLoader(f3::graphics::Device* device)
		{
			_device = device;
		}

		MeshLoader::~MeshLoader(void)
		{
		}

		bool MeshLoader::load(f3g::Mesh* mesh)
		{
			std::vector<f3m::Vector3f>& _v = mesh->_vertices;
			std::vector<f3m::Vector2f>& _t = mesh->_texturecoordinates;

			BufferDescription desc;

			// load vertex position data to device
			desc.size = sizeof(f3m::Vector3f) * _v.size();
			Buffer* target = NULL;
			_device->createBuffer(desc, &_v[0], &target);

			// load vertex texture-coordinates data to device
			desc.size = sizeof(f3m::Vector2f) * _t.size();
			Buffer* target2 = NULL;
			_device->createBuffer(desc, &_t[0], &target2);

			mesh->_buffer1 = target;
			mesh->_buffer2 = target2;

			VertexLayoutDefinition def;
			def.insert(def.end(), VertexLayoutElement("POSITION", 0, 0, X32Y32Z32, 3*sizeof(float)));
			def.insert(def.end(), VertexLayoutElement("TEXCOORD", 1, 1, U32V32, 2*sizeof(float)));
						
			mesh->_vertexlayoutdef = def;

			return true;
		}
	}
}