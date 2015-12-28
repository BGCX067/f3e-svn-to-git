#ifndef MESH_H
#define MESH_H

#include "Vector.h"
#include <vector>

namespace f3
{
	typedef unsigned short Index;

	class Mesh
	{
		
	public:
		std::vector<f3m::Vector3f> _vertices;
		std::vector<f3::Index> _indices;
		Mesh(void);
		~Mesh(void);
		unsigned int ib, vb;
	};
}
#endif