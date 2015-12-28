#include "Log.h"

Log* Log::_default = NULL;

Log::Log(void)
{
}

Log::~Log(void)
{
}

Log* Log::getDefault()
{
	if (_default == NULL)
		_default = new Log();
	
	return _default;
}

void Log::write(std::string str)
{
	write(L_INFO, str);
}

void Log::write(Level lvl, std::string str)
{
	std::cout << "<" << lvl << "\t> " << str << std::endl;
}

void Log::warning(std::string str)
{
	write(Level::L_WARNING, str);
}