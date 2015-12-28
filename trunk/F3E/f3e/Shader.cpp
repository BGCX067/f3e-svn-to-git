#include "Shader.h"

#include <sstream>
#include <algorithm>
#include <fstream>
#include <iterator>

#include <iostream>
#include <f3base/Log.h>

namespace f3
{
	namespace graphics
	{
		Shader::Shader(std::string name)
		{
			_pass = 0;
			_totalpasses = 1;
			_name = name;
		}

		Shader::~Shader(void)
		{
		}

		void Shader::begin()
		{
			_pass = 0;
		}

		f3::I32 Shader::currentPass()
		{
			return _pass;
		}

		void Shader::startPass()
		{
		
		}

		void Shader::endPass()
		{
			_pass++;
		}

		f3::I32 Shader::passCount()
		{
			return _totalpasses;
		}
	}
}
