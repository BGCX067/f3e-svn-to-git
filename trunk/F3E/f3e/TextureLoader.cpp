#include "TextureLoader.h"
#include <f3base/Common.h>
#include <sstream>
#include <algorithm>
#include <fstream>
#include <iterator>
#include <assert.h>

#include <iostream>
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

		bool TextureLoader::load(Texture* texture)
		{
			typedef std::istream_iterator<char> istream_iterator;
			typedef std::ostream_iterator<char> ostream_iterator;

			std::ifstream examplefile(texture->filename().c_str(), std::ios::binary);

			if (!examplefile.is_open())
			{ 
				f3u::log << "Error opening file: " << texture->filename() << "\n";
				return false;
			}

			long size = 0;
			

			// get length of file:
			examplefile.seekg (0,std::ios::end);
			size = examplefile.tellg();
			examplefile.seekg (0, std::ios::beg);

			// create buffer
			texture->_buffer = new char [size];
			texture->_size = size;

			// read data as a block:
			examplefile.read (texture->_buffer,size);

			// release file handle
			examplefile.close();


			return true;
		}

		//Texture* TextureLoader::load(std::string filename)
		//{
		//	/* needs to be implemented */
		//	return NULL;
		//}

		//Texture* TextureLoader::loadDummy()
		//{
		//	f3::I32 dimension = 128;
		//	f3::UI32 size = dimension * dimension * 4 /* 1 byte per channel RGBA*/;

		//	char* buffer = new char [size];

		//	//for (int i = 0; i < 127; i++)
		//	//	for (int j = 0; j < 127; j++)
		//	//	{
		//	//		buffer[i*j*4] = 240;
		//	//		buffer[i*j*4+1] = 240;
		//	//	}

		//	Texture* rslt = new Texture(buffer, size);
		//	rslt->setHeight(dimension);
		//	rslt->setWidth(dimension);

		//	return rslt;
		//}

		//Texture* TextureLoader::loadRaw(std::string filename, TextureDescription& texdesc)
		//{
		//	typedef std::istream_iterator<char> istream_iterator;
		//	typedef std::ostream_iterator<char> ostream_iterator;

		//	std::ifstream examplefile(filename.c_str(),std::ios::binary);

		//	if (!examplefile.is_open())
		//	{ 
		//		f3u::log << "Error opening file: " << filename << "\n";
		//		return loadDummy();
		//	}

		//	long size = 0;
		//	char* buffer = NULL;
		//	
		//	// get length of file:
		//	examplefile.seekg (0,std::ios::end);
		//	size = examplefile.tellg();
		//	examplefile.seekg (0, std::ios::beg);

		//	// create buffer
		//	buffer = new char [size];

		//	// read data as a block:
		//	examplefile.read (buffer,size);
		//	
		//	// release file handle
		//	examplefile.close();
		//	
		//	// create texture with buffer and texdesc
		//	Texture* rslt = new Texture(buffer, size);

		//	rslt->setHeight(texdesc.height);
		//	rslt->setWidth(texdesc.width);

		//	return rslt;
		//}

		//void TextureLoader::setMipMapLevels( int levels )
		//{
		//	_mipmaplevels = levels;
		//}

	}
}
