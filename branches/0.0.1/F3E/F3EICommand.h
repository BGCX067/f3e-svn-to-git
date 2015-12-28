#ifndef F3EICommand_H
#define F3EICommand_H

#include <string>

class F3EICommand
{
public:
	virtual void submit(std::string) = 0;
	virtual std::string getDesc() = 0;
	virtual std::string getCommandString() = 0;
};

#endif