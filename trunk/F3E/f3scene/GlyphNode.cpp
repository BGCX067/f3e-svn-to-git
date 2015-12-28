#include "Stdafx.h"

#include "GlyphNode.h"

namespace f3
{
	namespace scene
	{
		GlyphNode::GlyphNode(f3g::Mesh* mesh, char character, Node* parent) : MeshNode(mesh, GLYPH, parent)
		{
			_character = character;
		}

		GlyphNode::~GlyphNode(void)
		{
		}

	}

}