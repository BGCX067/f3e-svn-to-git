#ifndef SHADERMANAGER_H
#define SHADERMANAGER_H

#include <map>
#include <f3base/IDevice.h>
#include "Shader.h"

namespace f3
{
	namespace graphics
	{
		class ShaderManager
		{
			std::map<std::string, Shader*> shaders;
			IDevice* _device;

		public:
			ShaderManager(IDevice* device);
			void load(std::string shader);
		};
	}
}

#endif