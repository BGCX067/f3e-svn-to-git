#ifndef QUADMESH_H
#define QUADMESH_H

#include "Mesh.h"
#include <f3base/Common.h>

namespace f3
{

	class DLL QuadMesh : public Mesh
	{
	public:
		QuadMesh();
		~QuadMesh(void);
	};

}
#endif