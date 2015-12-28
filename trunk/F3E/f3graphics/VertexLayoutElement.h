#ifndef VertexLayoutElement_h__
#define VertexLayoutElement_h__

#include <f3base/Common.h>
#include <vector>

namespace f3
{
	namespace graphics
	{
		enum VertexFormat { X32Y32Z32, U32V32, R8G8B8A8, R32G32B32A32 };
		enum VertexDataType { PER_VERTEX, PER_INSTANCE };

		class VertexLayoutElement
		{

		public:
			std::string _semenaticName;
			f3::I32 _semanticSlot;
			f3::I32 _bufferSlot;
			f3::I32 _format;
			f3::I32 _stride;
			f3::I32 _type;
			f3::I32 _offset;
			VertexLayoutElement(std::string semanticName, f3::I32 semanticSlot, f3::I32 bufferSlot, f3::I32 format, f3::I32 stride, f3::I32 offset = 0, f3::I32 type = PER_VERTEX );
		};

		typedef std::vector<VertexLayoutElement> VertexLayoutDefinition;
	}
}

#endif // VertexLayoutElement_h__