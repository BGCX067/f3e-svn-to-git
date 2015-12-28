#ifndef SHADER_H
#define SHADER_H

#include <string>
#include <iostream>
#include <f3math/Matrix.h>
#include <f3base/Common.h>
#include "Texture.h"

namespace f3
{
	namespace graphics
	{
		class VertexLayout;
		class Device;

		class Shader
		{
			
		protected:
			std::string _name;
			f3::I32 _pass;
			f3::I32 _totalpasses;
			Device* _device;

		public:
			VertexLayout* _layout;
			Shader(Device* device, std::string name);
			~Shader(void);

			virtual f3::I32 compile() = 0;
			virtual void begin();
			virtual f3::I32 currentPass();
			virtual f3::I32 passCount();
			virtual void startPass();
			virtual void endPass();

			virtual void setTexture(f3g::Texture* texture) = 0;

			virtual void setProjectionMatrix(f3m::Matrix4f& matrix) = 0;
			virtual void setViewMatrix(f3m::Matrix4f& matrix) = 0;
			virtual void setWorldMatrix(f3m::Matrix4f& matrix) = 0;
		};
	}

}

#endif