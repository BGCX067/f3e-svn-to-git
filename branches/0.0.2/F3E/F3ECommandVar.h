#ifndef F3ECommandVar_H
#define F3ECommandVar_H

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

class DLL F3ECommandVar
{
public:
	enum Type { BOOL, INT, FLOAT, STRING, NONE };
	Type _type;
	std::string _name;
	std::string _desc;

	F3ECommandVar(Type type = NONE);
	~F3ECommandVar(void);
	virtual void parse(std::string in);
	
};

class DLL F3ECommandVarBool : public F3ECommandVar
{
public:
	bool _defaultValue;
	bool _value;

	F3ECommandVarBool(std::string name, std::string desc, bool v = false);
	void parse(std::string in);
};


class DLL F3ECommandVarInt : public F3ECommandVar
{
public:
	int _maxValue;
	int _minValue;
	int _defaultValue;
	int _value;

	F3ECommandVarInt(std::string name, std::string desc, int v = 0);
	void parse(std::string in);
};

#endif