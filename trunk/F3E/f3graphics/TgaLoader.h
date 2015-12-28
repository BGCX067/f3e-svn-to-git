#ifndef TgaLoader_h__
#define TgaLoader_h__

#include <f3base/Common.h>
#include <string>

namespace f3
{
	namespace graphics
	{
		class Texture;

		class TgaLoader
		{
		public:
			void TgaLoader::load( Texture* texture );
		};
	}
}

#endif // TgaLoader_h__