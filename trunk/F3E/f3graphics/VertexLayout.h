
#ifndef VertexLayout_h__
#define VertexLayout_h__

#include "VertexLayoutElement.h"

namespace f3
{
	namespace graphics
	{
		class VertexLayout
		{
		protected:
			VertexLayout(void) {};

		public:
			VertexLayoutDefinition _definition;
			virtual ~VertexLayout(void) {};
		};
	}
}

#endif // VertexLayout_h__