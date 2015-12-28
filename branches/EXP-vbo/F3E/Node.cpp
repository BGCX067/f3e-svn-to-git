#include "Node.h"
#include <algorithm>
#include <vector>
#include <iterator>
#include <sstream>

namespace f3
{
	Node::Node(Node* parent)
	{
		_parent = parent;
	}

	Node::~Node(void)
	{
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

	std::string Node::toString()
	{
		//std::string bla = "";
		std::stringstream iss(std::stringstream::in | std::stringstream::out);
		iss << "Node [Children: " << _children.size() << "]";
		
		return iss.str();
	}

	f3m::Vector3f Node::position()
	{
		return _position;
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