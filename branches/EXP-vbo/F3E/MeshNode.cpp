#include "MeshNode.h"

namespace f3
{

	MeshNode::MeshNode(Mesh* mesh, Node* parent) : Node(parent)
	{
		_mesh = mesh;
	}

	MeshNode::~MeshNode(void)
	{
	}

}