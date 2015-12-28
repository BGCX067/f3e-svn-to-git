#ifndef GlyphNode_h__
#define GlyphNode_h__

#include "MeshNode.h"

namespace f3
{
	class GlyphNode : public MeshNode
	{
	public:
		char _character;
		GlyphNode(Mesh* mesh, char character, Node* parent = NULL);
		~GlyphNode(void);
	};
}
#endif // GlyphNode_h__
