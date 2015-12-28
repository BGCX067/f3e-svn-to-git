#include "TextureLoader.h"
#include <f3base/Common.h>
#include <sstream>
#include <algorithm>
#include <fstream>
#include <iterator>
#include <assert.h>
#include <iostream>

#include "TgaLoader.h"

namespace f3
{
	namespace graphics
	{
		TextureLoader::TextureLoader(void) : _mipmaplevels(1)
		{
		}

		TextureLoader::~TextureLoader(void)
		{
		}

		bool TextureLoader::loadRaw(Texture* texture)
		{
			typedef std::istream_iterator<char> istream_iterator;
			typedef std::ostream_iterator<char> ostream_iterator;

			std::ifstream examplefile(texture->filename().c_str(), std::ios::binary);

			if (!examplefile.is_open())
			{ 
				f3u::log << "error opening file: " << texture->filename() << f3u::endl;
				return false;
			}

			long size = 0;


			// get length of file:
			examplefile.seekg (0,std::ios::end);
			size = examplefile.tellg();
			examplefile.seekg (0, std::ios::beg);

			// create buffer
			texture->_buffer = new f3::byte [size];
			texture->_size = size;

			// read data as a block:
			examplefile.read ((char*) texture->_buffer,size);

			// release file handle
			examplefile.close();
		}

		bool TextureLoader::load(Texture* texture)
		{
			std::string extension = texture->filename().substr(texture->filename().size()-3);
			
			if (extension.compare("raw") == 0)
			{
				loadRaw(texture);
			}
			else if (extension.compare("tga") == 0)
			{
				TgaLoader loader;
				loader.load(texture);
			}
			else
			{
				f3u::log << "failed to load texture with unknown extension: " << extension << f3u::endl;
				return false;
			}

			return true;
		}
	}
}
