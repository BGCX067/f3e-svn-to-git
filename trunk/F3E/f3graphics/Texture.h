#ifndef TEXTURE_H
#define TEXTURE_H

#include <f3base/Common.h>
#include <string>
#include "ShaderResource.h"

namespace f3
{
	namespace graphics
	{

		class TextureDescription
		{
		public:
			enum Format { R8G8B8A8 };

			Format format;
			int width;
			int height;
		};

		class Texture
		{

		private:
			std::string _filename;

		public:

			struct Format_R8G8B8A8
			{
				char r,g,b,a;
			};

			f3::byte* _buffer;
			long _size;
			TextureDescription _description;
			ShaderResource* _shaderResource;

			Texture(std::string filename);
			~Texture(void);

			f3::byte* buffer();
			long size();
			std::string filename();

		};


	}
}

namespace f3r = f3::graphics;

#endif