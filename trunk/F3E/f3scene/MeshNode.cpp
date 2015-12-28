#include "Stdafx.h"

#include "MeshNode.h"

namespace f3
{
	namespace scene
	{
		MeshNode::MeshNode(f3g::Mesh* mesh, Node* parent) : Node(Node::MESH, parent)
		{
			_mesh = mesh;
		}

		MeshNode::MeshNode(f3g::Mesh* mesh, NodeType nodeType, Node* parent) : Node(nodeType, parent)
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

}