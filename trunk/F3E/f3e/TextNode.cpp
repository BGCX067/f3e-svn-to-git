
#include "TextNode.h"
#include "Node.h"
#include "MeshNode.h"
#include "GlyphNode.h"

namespace f3
{
	TextNode::TextNode(f3::Font* font, std::string text, Node* parent) : Node(Node::Type::TEXT, parent)
	{
		const std::string::iterator end = text.end();
		const std::string::iterator current = text.begin();

		int count = 0;
		std::string::const_iterator i = text.begin();
		for(;i != text.end();++i)
		{
			f3::GlyphNode* mn = new f3::GlyphNode(font, f3::Node::Type::FONT);
			append(mn);
			mn->_character = *i;
			mn->setPosition(f3m::Vector3f(font->size()/2*count,0,0));
			++count;
		}
	}

	TextNode::~TextNode(void)
	{
	}

}

