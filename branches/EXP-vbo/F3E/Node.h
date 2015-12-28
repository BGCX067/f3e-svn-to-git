#ifndef NODE_H
#define NODE_H

#include <vector>
#include <string>
#include <sstream>
#include "Vector.h"

namespace f3
{
	class Node;
	typedef std::vector<Node*> NodeList;

	class Node
	{
	private:
		Node* _parent;
		NodeList _children;
		f3m::Vector3f _position;

	public:
		Node(Node* parent = NULL);
		~Node(void);

		void append(NodeList* nodes);
		void append(Node* node);
		void detach(Node* node);
		void setParent(Node* parent);
		NodeList* children();
		bool hasChildren();
		std::string toString();
		void render();
		f3m::Vector3f position();
		void setPosition(f3m::Vector3f position);
	};

}

#endif