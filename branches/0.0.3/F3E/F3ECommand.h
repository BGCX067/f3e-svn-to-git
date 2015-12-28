#ifndef F3ECommand_H
#define F3ECommand_H

#ifndef EXPORTDLL
#define DLL __declspec(dllimport)
#else 
#define DLL __declspec(dllexport)
#endif

#include <iostream>
#include <string>
#include <vector>
#include "F3ECommandVar.h"
#include "F3EICommand.h"

class DLL F3ECommand : public F3EICommand
{
public:
	std::string command;
	F3ECommand(std::string command);
	~F3ECommand(void);
	void addParameter(F3ECommandVar* parameter);
	std::string F3ECommand::getDesc();
	std::vector<F3ECommandVar*> parameters;
	void submit(std::string input);
	std::string getCommandString();
	
};

#endif