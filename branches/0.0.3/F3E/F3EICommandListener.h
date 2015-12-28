#ifndef F3EICommandListener_H
#define F3EICommandListener_H

#ifndef EXPORTDLL
#define DLL __declspec(dllimport)
#else 
#define DLL __declspec(dllexport)
#endif

#include <iostream>
#include <string>
#include <map>
#include <sstream>
#include <algorithm>
#include <iterator>
#include "F3ECommand.h"

class F3EICommandListener
{
public:
	virtual void execute(F3EICommand* c) = 0;
};

#endif