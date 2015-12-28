#ifndef Buffer_h__
#define Buffer_h__

#include <f3base/Common.h>
#include "VertexLayoutElement.h"

namespace f3
{
	namespace graphics
	{
		typedef unsigned short Index;

		enum BufferType { VERTEX_BUFFER, INDEX_BUFFER };
		
		class BufferDescription
		{
		public:
			f3::UI32 size;
			BufferType type;

			BufferDescription() : type(VERTEX_BUFFER), size(0) {};
		};

		class Buffer
		{
		protected:
			Buffer()  {};
		public:
			VertexLayoutDefinition _vertexLayout;

		};
	}
}
#endif // Buffer_h__
