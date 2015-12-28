#ifndef ISHADERLOADER_H
#define ISHADERLOADER_H

#include "Common.h"

namespace f3
{
	namespace graphics 
	{
		class Shader;

		class IShaderLoader
		{
		public:
			virtual Shader* load(std::string shadername) = 0;
		};
	}
}
#endif