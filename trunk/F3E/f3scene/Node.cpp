#include "Stdafx.h"

#include "Node.h"
#include <algorithm>
#include <vector>
#include <iterator>
#include <sstream>

namespace f3
{
	namespace scene
	{

		Node::Node(NodeType type, Node* parent)
		{
			_type = type;
			_parent = parent;
			_object = f3m::Matrix4f::identity();
			rot = 0.0f;
			_position._x = 0.0f;
			_position._y = 0.0f;
			_position._z = 0.0f;
		}

		Node::~Node(void)
		{
		}

		void* Node::data()
		{
			return NULL;
		}

		void Node::setParent(Node* parent)
		{
			_parent = parent;
		}

		void Node::append(NodeList* nodes)
		{

			_children.insert(_children.end(), nodes->begin(), nodes->end());
		}

		void Node::append(Node* node)
		{
			node->setParent(this);
			_children.insert(_children.end(), node);
		}

		void Node::detach(Node* node)
		{
			std::remove(_children.begin(), _children.end(), node);
		}

		bool Node::isType(NodeType type)
		{
			if (_type == type)
				return true;

			return false;
		}
		std::string Node::toString()
		{
			//std::string bla = "";
			std::stringstream iss(std::stringstream::in | std::stringstream::out);
			iss << "Node [Children: " << _children.size() << "]";

			return iss.str();
		}

		f3m::Vector3f& Node::position()
		{
			return _position;
		}

		Node* Node::parent()
		{
			return _parent;
		}

		void Node::setPosition(f3m::Vector3f position)
		{
			_position = position;
		}

		NodeList* Node::children()
		{
			return &_children;
		}


		bool Node::hasChildren()
		{
			if (_children.size() <= 0)
				return false;

			return true;
		}
	}
}