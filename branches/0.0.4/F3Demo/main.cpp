//#define EXPORTDLL
//#include "F3ECommandManager.h"
#include <iostream>
#include "F3EMain.h"
//
//class Test : public F3EICommandListener
//{
//public:
//	void execute(F3EICommand* c)
//	{
//		std::cout << "cmd: " << c->getCommandString() << std::endl;
//	};
//};
//
class App : public F3EIApplication
{
	void OnInit() { std::cout << "init" <<std::endl; };
	void OnUpdate() {};
	void OnExit() {};
};

void main()
{
	//std::string query;
	//std::stringbuf buffer;

	f3e::start(new App());

	//F3ECommandManager cm;
	//
	//F3ECommand* command1 = new F3ECommand("sv_servername");
	//command1->addParameter(new F3ECommandVarBool("shouldbebool","a 255 character long servername"));
	//command1->addParameter(new F3ECommandVarInt("shouldbeint","numeric value 0-8000"));

	//F3ECommand* command2 = new F3ECommand("exit");
	//
	//Test t;
	//cm.addListener(&t);
	//cm.add(command1);
	//cm.add(command2);

	//std::cout << command1->getDesc();
	//
	//while (0==0)
	//{
	//	try 
	//	{
	//		//cm.submit("sv_servername true -1");
	//		//std::cin >> inputstr;
	//		query = "";
	//		std::cout << "> ";// Type something with spaces here. e.g ( "financial instruments being traded on the American stock exchange" );
	//
	//		std::getline(std::cin,query);
	//		cm.submit(query);
	//	}
	//	catch (std::exception e)
	//	{
	//		std::cout << e.what() << std::endl;
	//		system("PAUSE");
	//		return;
	//	}

	//
	////COORD co = {width,height};
	////SetConsoleScreenBufferSize(__hStdOut, co);

	//	//WindowUpdate();
	//}

	return;
}