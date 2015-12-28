#ifndef MESHNODE_H
#define MESHNODE_H

#include "Node.h"
#include "Mesh.h"

namespace f3
{

	class DLL MeshNode : public Node
	{
		Mesh* _mesh;

	public:
		MeshNode(Mesh* mesh, Node* parent = NULL);
		MeshNode(Mesh* mesh, Node::Type nodeType, Node* parent = NULL);
		~MeshNode(void);
		void* data();
	};

}
#endif