#ifndef Buffer_h__
#define Buffer_h__

#include <f3base/Common.h>
#include <d3d10.h>
#include <GL/glew.h>

namespace f3
{
	namespace graphics
	{
		class BufferDescription
		{
		public:
			f3::UI32 size;
		};

		class Buffer
		{
		public:
			ID3D10Buffer* _buffer;
			GLuint _glbuffer;

		};
	}
}
#endif // Buffer_h__
