
#include "TgaLoader.h"
#include "TgaFile.h"

#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
#include <iterator>
#include <fstream>
#include <assert.h>
#include "Texture.h"

namespace f3
{
	namespace graphics
	{
		void TgaLoader::load( Texture* texture )
		{
			std::string filename(texture->filename());
			TgaFile file;

			f3u::log << f3u::info << "loading tga file: " << filename << "\n"; 

			typedef std::istream_iterator<char> istream_iterator;
			typedef std::ostream_iterator<char> ostream_iterator;

			std::ifstream filestream(filename, std::ios::binary);

			if (!filestream.is_open())
			{ 
				f3u::log << f3u::warning << "error opening tga file: " << filename << f3u::endl;
			}

			long size = 0;

			filestream.read((char*) &file.header, sizeof(TgaFileHeader));

			// if id field exists read it
			if (file.header.idSize != 0)
			{
				file.id = new f3::byte[file.header.idSize];
				filestream.read((char*)file.id, file.header.idSize);
			}

			// if color map type not zero read color map
			if (file.header.colorMapType != 0)
			{

			}

			// read image data field
			if (file.header.imageSpecification.pixelSize % 8 != 0)
			{
				//invalid pixel format
				return;
			}
			TgaImageSpecification& img_spec(file.header.imageSpecification);

			int bytes_per_pixel = img_spec.pixelSize / 8;
			long data_size = bytes_per_pixel * bytesAsInt(img_spec.width) * bytesAsInt(img_spec.height);
			file.imageData = new f3::byte[data_size];
			
			for (int i = 0; i < data_size; i+=4)
			{
				filestream.read((char*)(&file.imageData[i+2]), 1);
				filestream.read((char*)(&file.imageData[i+1]), 1);
				filestream.read((char*)(&file.imageData[i+0]), 1);
				filestream.read((char*)(&file.imageData[i+3]), 1);
			}
			filestream.close();

			texture->_buffer = file.imageData;
			texture->_size = data_size;
			texture->_description.height = bytesAsInt(img_spec.height);
			texture->_description.width = bytesAsInt(img_spec.width);
			texture->_description.format = TextureDescription::R8G8B8A8;
			return;
		}
	}

}
