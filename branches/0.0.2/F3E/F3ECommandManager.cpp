#define EXPORTDLL
#include "F3ECommandManager.h"

F3ECommandManager::F3ECommandManager(void)
{
}

F3ECommandManager::~F3ECommandManager(void)
{
}

void F3ECommandManager::add(F3EICommand* command)
{
	commands.insert(std::pair<std::string, F3EICommand*>(command->getCommandString(), command));
}

void F3ECommandManager::submit(std::string input)
{
	// command token
	std::string token = "";

	// create string stream from input
	std::istringstream iss(input);
	
	// get first token
	std::getline(iss, token,' ');

	// search for token in command list
	std::map<std::string, F3EICommand*>::iterator itr = commands.find(token);

	// if no command is found return
	if (itr == commands.end())
	{
		throw std::exception("unrecognised command");
		return;
	}

	// get the rest of the command string (in string minus first token)
	std::getline(iss, input);
	
	// submit string to command for parsing/handling
	itr->second->submit(input);

	// calls the connected listner methods
	std::list<F3EICommandListener*>::iterator citr = listener.begin();

	while(citr != listener.end())
	{
		(*citr)->execute(itr->second);
		citr++;
	}
}

void F3ECommandManager::addListener(F3EICommandListener* listener)
{
	this->listener.insert(this->listener.begin(), listener);
}

void F3ECommandManager::remListener(F3EICommandListener* listener)
{
	this->listener.remove(listener);
}