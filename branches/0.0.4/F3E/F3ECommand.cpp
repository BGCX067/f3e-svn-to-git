#define EXPORTDLL
#include "F3ECommand.h"

F3ECommand::F3ECommand(std::string command)
{
	this->command = command;
}

F3ECommand::~F3ECommand(void)
{
}


void F3ECommand::addParameter(F3ECommandVar* parameter)
{
	parameters.insert(parameters.begin(), parameter);
}

std::string F3ECommand::getDesc()
{
	std::string rslt = command;
	std::string paramdesc = "";

	// start analysing parameters
	std::vector<F3ECommandVar*>::iterator param = parameters.begin();

	// loop through parameters
	for (param = parameters.begin(); param != parameters.end(); param++)
	{
		rslt += " [" + (*param)->_name + "]";
		paramdesc += "\n\t" + (*param)->_name + ":\t" + (*param)->_desc;
	}

	return (rslt + paramdesc + "\n");
}

std::string F3ECommand::getCommandString()
{
	return this->command;
}

void F3ECommand::submit(std::string input)
{
	std::vector<std::string> tokens;
	std::istringstream iss(input);
	std::string elem;

	//if (parameters.size() == 1)
	//{
	//	// no need for advanced lookups the whole string is the value
	//	(*parameters.begin())->parse();
	//	return;
	//}

	// actual split
	while (std::getline(iss, elem, ' '))
		tokens.insert(tokens.begin(), elem);

	// start analysing parameters
	std::vector<std::string>::iterator token = tokens.begin();

	// start analysing parameters
	std::vector<F3ECommandVar*>::iterator param = parameters.begin();

	if (parameters.size() != tokens.size())
	{
		std::cout << getDesc();
		std::cout << "(parameters count: " << parameters.size() << " ";
		std::cout << "tokens count: " << tokens.size() << ")" << std::endl;
		return;
	}

	// loop through parameters
	while(param != parameters.end() && token != tokens.end())
	{
		F3ECommandVar* p = (*param);
		std::cout << p->_name << ":\t" << (*token) << std::endl;
		std::cout << "info:\t\ttrying to parse" << std::endl;

		std::stringstream ss(*token);
		
		try
		{
			p->parse(*token);
		}
		catch (std::exception e)
		{
			std::cout << "exception:\t" << e.what() << std::endl;
			break;
		}

		token++;
		param++;
	}

}