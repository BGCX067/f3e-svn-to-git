#include "VertexLayoutElement.h"

namespace f3
{
	namespace graphics
	{
		VertexLayoutElement::VertexLayoutElement( std::string semanticName, f3::I32 semanticSlot, f3::I32 bufferSlot, f3::I32 format, f3::I32 stride, f3::I32 offset, f3::I32 type )
		{
			_semenaticName = semanticName;
			_semanticSlot = semanticSlot;
			_bufferSlot = bufferSlot;
			_format = format;
			_stride = stride;
			_type = type;
			_offset = offset;
		}
	}
}