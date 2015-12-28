#ifndef QuadMesh_h__
#define QuadMesh_h__

#include <f3base/Common.h>
#include "Mesh.h"

namespace f3
{
	namespace graphics
	{

		class QuadMesh : public Mesh
		{
		public:
			QuadMesh();
			virtual ~QuadMesh(void);
		};

	}
}


#endif // QuadMesh_h__