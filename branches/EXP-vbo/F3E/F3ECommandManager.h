#ifndef F3ECommandManager_H
#define F3ECommandManager_H

#ifndef EXPORTDLL
#define DLL __declspec(dllimport)
#else 
#define DLL __declspec(dllexport)
#endif

#include <iostream>
#include <string>
#include <list>
#include <map>
#include <sstream>
#include <algorithm>
#include <iterator>

#include "F3ECommand.h"
#include "F3EICommandListener.h"

class DLL F3ECommandManager
{	
	std::map<std::string, F3EICommand*> commands;
	std::list<F3EICommandListener*> listener;

public:
	
	F3ECommandManager(void);
	~F3ECommandManager(void);

	void add(F3EICommand* command);
	void submit(std::string input);
	void addListener(F3EICommandListener* listener);
	void remListener(F3EICommandListener* listener);

};

#endif
