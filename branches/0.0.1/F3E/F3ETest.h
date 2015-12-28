//#include "main.h"
#ifndef EXPORTDLL
#define DLL __declspec(dllimport)
#else 
#define DLL __declspec(dllexport)
#endif


class DLL F3ETest
{
	int test_;
public:
	F3ETest(void) { test_ = 1; };
	~F3ETest(void) {};
	int test() { return (test_+=1); };
};
