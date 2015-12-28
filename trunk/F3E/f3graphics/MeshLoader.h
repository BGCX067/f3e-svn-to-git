#ifndef MeshLoader_H
#define MeshLoader_H

#include <f3base/Common.h>
#include <f3base/IMeshLoader.h>

namespace f3
{
	namespace graphics
	{
		class Device;
		class Mesh;

		class MeshLoader : public IMeshLoader
		{
			f3::graphics::Device* _device;

		public:
			MeshLoader(Device* device);
			~MeshLoader(void);
			bool load(f3g::Mesh* mesh);
		};
	}
}

#endif