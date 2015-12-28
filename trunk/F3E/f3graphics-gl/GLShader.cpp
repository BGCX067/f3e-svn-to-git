#include "GLShader.h"

#include <f3base/Common.h>
#include <sstream>
#include <algorithm>
#include <fstream>
#include <iterator>

#include <iostream>
#include <f3graphics/TextureLoader.h>
#include "GLTextureLoader.h"
#include "GLTexture.h"
#include <f3math\Matrix.h>
#include <f3graphics/VertexLayoutElement.h>
#include <f3graphics/Device.h>

namespace f3
{
	namespace graphics
	{

		GLShader::GLShader(Device* device, std::string name) : Shader(device, name)
		{
			_program = 0;


			std::string path = "resources/shader/glsl/";
			std::string extension = ".glsl";
			ps = loadFromFile(path+name+"_ps"+extension);
			vs = loadFromFile(path+name+"_vs"+extension);
		}

		GLShader::~GLShader(void)
		{
		}

		std::string GLShader::loadFromFile(std::string filename)
		{
			typedef std::istream_iterator<char> istream_iterator;
			typedef std::ostream_iterator<char> ostream_iterator;

			std::stringstream iss(std::stringstream::in | std::stringstream::out);
			std::ifstream examplefile(filename.c_str(),std::ios::binary);

			if (!examplefile.is_open())
			{ 
				std::cout << "Error opening file: " << filename;
				return "";
			}

			iss << examplefile.rdbuf();
			examplefile.close();

			return iss.str();
		}


		void GLShader::printShaderInfoLog(const GLuint &shader)
		{
			GLint buffersize = 0;
			glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &buffersize);

			GLchar* buffer = new GLchar[buffersize];

			if (buffersize == 0 || buffersize == 1)
				return;

			glGetShaderInfoLog(shader, buffersize, NULL, &buffer[0]);
			std::string ob(buffer);
			ob.pop_back();
			f3u::log << f3u::info << ob << f3u::endl;
		}

		void GLShader::printProgramInfoLog(const GLuint &program)
		{
			GLint buffersize = 0;
			glGetProgramiv(program, GL_INFO_LOG_LENGTH, &buffersize);
			
			GLchar* buffer = new GLchar[buffersize];

			if (buffersize == 0 || buffersize == 1)
				return;

			glGetProgramInfoLog(program, buffersize, NULL, &buffer[0]);
			std::string ob(buffer);
			ob.pop_back();
			f3u::log << f3u::info << ob << f3u::endl;
		}

		f3::I32 GLShader::compile()
		{
			if (!glewIsExtensionSupported("GL_ARB_explicit_attrib_location"))
				return -1;

			if (vs.compare("") == 0 || ps.compare("") == 0)
				return -1;

			f3u::log << f3u::info << "GLSL: Compiling Shader (" << _name << ")" << f3u::endl;
			
			// compile vertex shader
			GLuint vertexshader = glCreateShader(GL_VERTEX_SHADER);
			const char* vs_source = vs.c_str();
			glShaderSource(vertexshader, 1, &vs_source, NULL);;
			glCompileShader(vertexshader);
			printShaderInfoLog(vertexshader);

			// compile fragment shader
			GLuint fragmentshader = glCreateShader(GL_FRAGMENT_SHADER);	
			const char* fs_source = ps.c_str();
			glShaderSource(fragmentshader, 1, &fs_source, NULL);
			glCompileShader(fragmentshader);
			printShaderInfoLog(fragmentshader);

			// create program
			_program = glCreateProgram();
			glAttachShader(_program,vertexshader);
			glAttachShader(_program,fragmentshader);
			glLinkProgram(_program);
			printProgramInfoLog(_program);

			VertexLayoutDefinition def;
			def.insert(def.end(), VertexLayoutElement("POSITION", 0, 0, X32Y32Z32, 3*sizeof(float)));
			def.insert(def.end(), VertexLayoutElement("TEXCOORD", 1, 1, U32V32, 2*sizeof(float)));

			_device->createVertexLayout(&def, this, &this->_layout);

			_world = glGetUniformLocation(_program, "World");
			_view = glGetUniformLocation(_program, "View");
			_projection = glGetUniformLocation(_program, "Projection");
			glUseProgram(_program);
			
			return 0;
		}

		void GLShader::begin()
		{
			_pass = 0;
			glUseProgram(_program);
		}

		void GLShader::setProjectionMatrix( f3m::Matrix4f& matrix )
		{
			glUniformMatrix4fv(_projection, 1, false,(float*)&(matrix));
		}

		void GLShader::setViewMatrix( f3m::Matrix4f& matrix )
		{
			glUniformMatrix4fv(_view, 1, false,(float*)&(matrix));
		}

		void GLShader::setWorldMatrix( f3m::Matrix4f& matrix )
		{
			glUniformMatrix4fv(_world, 1, false,(float*)&(matrix));
		}

		GLuint GLShader::program()
		{
			return _program;
		}

		void GLShader::setTexture(f3g::Texture* texture)
		{
			f3r::GLTexture* glTexture = (f3r::GLTexture*) texture->_shaderResource;
			glActiveTexture(GL_TEXTURE0 + 0);
			glBindTexture(GL_TEXTURE_2D, glTexture->data());
		}

	}

}