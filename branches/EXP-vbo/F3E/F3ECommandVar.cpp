#define EXPORTDLL
#include "F3ECommandVar.h"

F3ECommandVar::F3ECommandVar(Type type)
{
	_type = type;
}
	
F3ECommandVar::~F3ECommandVar(void)
{
}

void F3ECommandVar::parse(std::string in) 
{
}

F3ECommandVarBool::F3ECommandVarBool(std::string name, std::string desc, bool v) : F3ECommandVar(BOOL)
{
	_name = name;
	_desc = desc;
	_defaultValue = v;
	_value = _defaultValue;
}

void F3ECommandVarBool::parse(std::string in)
{
	//std::cout << "kommtan: " << in << std::endl;
	if (in == "true")
		_value = true;
	else if (in == "false")
		_value = false;
	else
	{
		throw std::exception("unable to parse");
	}
	std::cout << "parse successful: " << _value << std::endl;
}


F3ECommandVarInt::F3ECommandVarInt(std::string name, std::string desc, int v) : F3ECommandVar(INT)
{
	_name = name;
	_desc = desc;
	_defaultValue = v;
	_value = _defaultValue;
	_minValue = 0;
	_maxValue = 30000;
}

void F3ECommandVarInt::parse(std::string in)
{
	std::stringstream ss(in);

	if((ss >> _value).fail())
	{ 
		throw std::exception("unable to parse value");
	}
	std::cout << "parse successful: " << _value << std::endl;

	if (_value < _minValue || _value > _maxValue)
	{
		throw std::exception("value out of bounds");
	}
	
}