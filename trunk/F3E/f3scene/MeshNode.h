#ifndef MESHNODE_H
#define MESHNODE_H

#include "Node.h"


namespace f3
{
	namespace graphics
	{
		class Mesh;
	}

	namespace scene
	{
		class MeshNode : public Node
		{
			f3g::Mesh* _mesh;

		public:
			MeshNode(f3g::Mesh* mesh, Node* parent = NULL);
			MeshNode(f3g::Mesh* mesh, Node::NodeType nodeType, Node* parent = NULL);
			~MeshNode(void);
			void* data();
		};

	}

}
#endif