#ifndef ShaderLoader_h__
#define ShaderLoader_h__

#include <f3base/IShaderLoader.h>

namespace f3
{
	namespace graphics
	{
		template < typename T_DEVICE, typename T_SHADER >

		class ShaderLoader : public IShaderLoader
		{
			T_DEVICE* _device;

		public:
			ShaderLoader(T_DEVICE* device) : _device(device) {};

			virtual T_SHADER* load(std::string shadername)
			{
				T_SHADER* shader = new T_SHADER(_device,shadername);

				f3::I32 rslt = shader->compile();

				// if shader compile fails and is fallback assert
				assert(!(rslt != 0 && shadername.compare("fallback") == 0));

				// if shader compile fails try to load fallback
				if (rslt == -1)
					return load("fallback");

				return shader;
			}
		};
	}
}
#endif // ShaderLoader_h__
