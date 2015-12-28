#include "MeshNode.h"

namespace f3
{

	MeshNode::MeshNode(Mesh* mesh, Node* parent) : Node(Node::Type::MESH, parent)
	{
		_mesh = mesh;
	}

	MeshNode::MeshNode(Mesh* mesh, Node::Type nodeType, Node* parent) : Node(nodeType, parent)
	{
		_mesh = mesh;
	}


	MeshNode::~MeshNode(void)
	{
	}

	void* MeshNode::data()
	{
		return _mesh;
	}

}