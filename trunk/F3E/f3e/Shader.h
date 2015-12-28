#ifndef SHADER_H
#define SHADER_H

#include <string>
#include <iostream>
#include <f3math/Matrix.h>
#include <f3base/Common.h>

namespace f3
{
	namespace graphics
	{

		class Shader
		{
			f3::I32 _pass;
			f3::I32 _totalpasses;

		protected:
			std::string _name;

		public:
			Shader(std::string name);
			~Shader(void);

			virtual f3::I32 compile() = 0;
			virtual void begin();
			virtual f3::I32 currentPass();
			virtual f3::I32 passCount();
			virtual void startPass();
			virtual void endPass();

			virtual void setProjectionMatrix(f3m::Matrix4f& matrix) = 0;
			virtual void setViewMatrix(f3m::Matrix4f& matrix) = 0;
			virtual void setWorldMatrix(f3m::Matrix4f& matrix) = 0;
		};
	}

}

#endif