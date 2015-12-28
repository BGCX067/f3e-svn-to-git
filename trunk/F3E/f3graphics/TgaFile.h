#ifndef TgaFile_h__
#define TgaFile_h__


#include <f3base/Common.h>

#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
#include <iterator>
#include <fstream>
#include <assert.h>

namespace f3
{
	typedef unsigned char byte;


class TgaColorMapSpecification
{
	f3::byte origin[2];								// Color Map Origin.
	f3::byte length[2];								// Color Map Length.
	f3::byte entrySize;								// Color Map Entry Size.  
};

class TgaImageSpecification 
{
public:
	f3::byte xOrigin[2];							// X Origin
	f3::byte yOrigin[2];							// Y Origin
	f3::byte width[2];								// Width
	f3::byte height[2];								// Height
	f3::byte pixelSize;								// Image Pixel Size.
	f3::byte descriptorByte;						// Image Descriptor Byte.
};

class TgaFileHeader
{
public:
	f3::byte idSize;								// Number of Characters in Identification Field. 
	f3::byte colorMapType;							// Color Map Type.
	f3::byte imageTypeCode;							// Image Type Code.
	TgaColorMapSpecification colorMapSpecification;	// Color Map Specification.
	TgaImageSpecification imageSpecification;		// Image Specification.
};

class TgaFile
{
public:
	TgaFileHeader header;
	f3::byte* id;									// Image Identification Field.
	f3::byte* colorMapData;							// Color map data. 
	f3::byte* imageData;							// Image Data Field.
};


inline int bytesAsInt( const f3::byte* bytes )
{
	return (int) (bytes[1] << 8) + bytes[0];
}

};
#endif // TgaFile_h__

