#ifndef TextRenderer_h__
#define TextRenderer_h__

#include <f3base/Common.h>
#include <f3graphics/VertexLayoutElement.h>
#include "Buffer.h"
#include "DebugContext.h"
#include "Texture.h"
#include <f3base/ColorRGBA.h>

namespace f3
{
	namespace graphics
	{
		struct MatrixSetup;
		class Shader;
		class Device;
		class VertexLayout;
		
		class Character
		{
		public:
			float x;
			float y;
			float width;
			float height;
		};

		class CharacterInstanceData
		{
		public:
			f3m::Vector3f position;
			f3u::ColorRGBA color;
			CharacterInstanceData() {};
			CharacterInstanceData(f3m::Vector3f position, f3u::ColorRGBA color ) : position(position), color(color) {};
		};

		class TextRenderer
		{
			Texture* _texture;
			DebugContext* _context;
			VertexLayout* _vertexLayout;
			Buffer* _buffer;
			Buffer* _uvbuffer;
			Buffer* _posbuffer;
			Buffer* _indexbuffer;


			std::vector<RenderString>& _strings;

			std::vector<f3m::Vector2f> _vbdata;
			f3g::Device* _device;
			Shader* _shader; 

		protected:
			float _size;
			Character _characters[255];

		public:
			MatrixSetup* _matrices;
			TextRenderer(f3g::Device* device, DebugContext* context);
			~TextRenderer(void);

			void render();
			void setupMatrices();
		};
	}
}


#endif // TextRenderer_h__
