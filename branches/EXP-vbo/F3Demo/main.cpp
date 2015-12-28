//#define EXPORTDLL
//#include "F3ECommandManager.h"
#include <iostream>
#include "../F3E/Main.h"
#include "main.h"

class testapp : public IApplication
{
	void OnInit() {}
	void OnUpdate() {}
	void OnExit() {}
};

void main()
{
	f3e::start(new testapp());

	return;
}