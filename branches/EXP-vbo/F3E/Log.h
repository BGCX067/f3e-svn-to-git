#ifndef LOG_H
#define LOG_H

#include "Common.h"
#include <iostream>
#include <string>

class Log
{
	static Log* _default;

public:
	enum Level { L_FATAL_ERROR = -1, L_ERROR = -10, L_WARNING = -1000, L_INFO = 1, L_MSG = 100 };

	Log(void);
	~Log(void);
	static Log* getDefault();
	void write(std::string str);
	void warning(std::string str);
	void write(Level lvl, std::string str);
};

#endif