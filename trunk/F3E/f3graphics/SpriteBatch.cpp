#include "SpriteBatch.h"

namespace f3
{
	namespace graphics
	{
		SpriteBatch::SpriteBatch(void)
		{
		}
		
		SpriteBatch::~SpriteBatch(void)
		{
		}

		void SpriteBatch::draw( f3m::Vector3f position, f3g::Texture* texture, f3::F32 size /*= 1.0f*/, f3::F32 rotation /*= 0.0f*/ )
		{
			SpriteBatchEntry entry;
			entry.position = position;
			entry.texture = texture;
			entry.size = size;
			entry.rotation = rotation;

			_sprites.insert(_sprites.end(), entry);
		}

	}
}
