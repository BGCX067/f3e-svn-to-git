#ifndef GlyphNode_h__
#define GlyphNode_h__

#include "MeshNode.h"

namespace f3
{
	namespace scene
	{
		class GlyphNode : public MeshNode
		{
		public:
			char _character;
			GlyphNode(f3g::Mesh* mesh, char character, Node* parent = NULL);
			~GlyphNode(void);
		};

	}
}
#endif // GlyphNode_h__
