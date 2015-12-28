#ifndef SpriteBatch_h__
#define SpriteBatch_h__

#include <f3base/Common.h>
#include <f3math/Vector.h>
#include "Texture.h"
#include <vector>

namespace f3
{
	namespace graphics
	{
		struct SpriteBatchEntry
		{
			f3m::Vector3f position;
			f3g::Texture* texture;
			f3::F32 size;
			f3::F32 rotation;
		};

		typedef std::vector<SpriteBatchEntry> SpriteList;

		class SpriteBatch
		{
		public:
			SpriteList _sprites;
			
			SpriteBatch(void);
			~SpriteBatch(void);
			void begin();
			void draw(f3m::Vector3f position, f3g::Texture* texture, f3::F32 size = 1.0f, f3::F32 rotation = 0.0f);
			void end();
		};
	}
}
#endif // SpriteBatch_h__
