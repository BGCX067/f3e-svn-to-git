#ifndef NODE_H
#define NODE_H

#include <vector>
#include <string>
#include <sstream>
#include <f3math/Vector.h>
#include <f3math/Matrix.h>
#include <f3base/Common.h>

namespace f3
{
	class Node;
	typedef std::vector<Node*> NodeList;

	class DLL Node
	{
	public:
		enum Type { DEFAULT, MESH, CAMERA, FONT, TEXT, GLYPH };

	private:
		Node* _parent;
		NodeList _children;
		f3m::Vector3f _position;
		Type _type;

	public:
		f3m::Matrix4f _object;
		float rot;
		Node(Type type = DEFAULT, Node* parent = NULL);
		~Node(void);

		void append(NodeList* nodes);
		void append(Node* node);
		void detach(Node* node);
		void setParent(Node* parent);
		NodeList* children();
		bool hasChildren();
		std::string toString();
		void render();
		f3m::Vector3f& position();
		Node* parent();
		void setPosition(f3m::Vector3f position);
		virtual void* data();
		bool isType(Type type);
	};

}

#endif