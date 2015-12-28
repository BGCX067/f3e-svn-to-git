#ifndef GLSHADER_H
#define GLSHADER_H

#include <f3base/Common.h>
#include <f3graphics/Shader.h>
#include <f3graphics/Texture.h>

#include "F3GL.h"

namespace f3
{
	namespace graphics
	{
		class Device;

		class GLShader : public Shader
		{
			GLuint _program;
			std::string ps;
			std::string vs;
			std::string loadFromFile(std::string filename);
			int _view, _world, _projection;

		public:
			int _vertex, _texcoord0, _normal;
			GLuint program();
			GLShader(Device* device, std::string name);
			~GLShader(void);
			f3::I32 compile();
			void begin();
	
			void setProjectionMatrix(f3m::Matrix4f& matrix);
			void setViewMatrix(f3m::Matrix4f& matrix);
			void setWorldMatrix(f3m::Matrix4f& matrix);
			void setTexture(f3g::Texture* texture);
			void printShaderInfoLog(const GLuint &shader);
			void printProgramInfoLog(const GLuint &program);
		};
	}
}

#endif