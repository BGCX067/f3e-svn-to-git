#include "ShaderManager.h"

namespace f3
{
	namespace graphics
	{
		typedef std::pair<std::string, Shader*> ShaderEntry;

		ShaderManager::ShaderManager(IDevice* device)
		{
			_device = device;
			load("default");
			load("fallback");
		}

		void ShaderManager::load(std::string shadername)
		{
			Shader* shader = _device->getShaderLoader()->load(shadername);			
			shaders.insert(shaders.end(), ShaderEntry(shadername, shader));
		}
	}
}