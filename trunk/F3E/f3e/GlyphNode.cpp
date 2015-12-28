
#include "GlyphNode.h"

namespace f3
{

	GlyphNode::GlyphNode(Mesh* mesh, char character, Node* parent) : MeshNode(mesh, Node::Type::GLYPH, parent)
	{
		_character = character;
	}

	GlyphNode::~GlyphNode(void)
	{
	}

}