#ifndef IMESHLOADER_H
#define IMESHLOADER_H

#include <f3base/Common.h>

namespace f3
{
	namespace graphics 
	{

		class Mesh;

		class IMeshLoader
		{
		public:
			virtual bool load(f3g::Mesh* mesh) = 0;
		};
	}
}
#endif