#ifndef RenderTarget_h__
#define RenderTarget_h__

#include <f3base/Common.h>

namespace f3
{
	namespace graphics
	{
		class RenderTargetDescription
		{
		public:
			f3::I32 _width;
			f3::I32 _height;
		};

		class RenderTarget
		{
		public:
			Texture* texture;
			RenderTargetDescription desc;
		};
	}
}

#endif // RenderTarget_h__
