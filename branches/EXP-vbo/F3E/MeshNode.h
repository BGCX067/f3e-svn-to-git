#ifndef MESHNODE_H
#define MESHNODE_H

#include "Node.h"
#include "Mesh.h"

namespace f3
{

class MeshNode : public Node
{
	Mesh* _mesh;

public:
	MeshNode(Mesh* mesh, Node* parent = NULL);
	~MeshNode(void);
};

}
#endif