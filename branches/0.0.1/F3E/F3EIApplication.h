#ifndef F3EIApplication_H
#define F3EIApplication_H

#ifndef EXPORTDLL
#define DLL __declspec(dllimport)
#else 
#define DLL __declspec(dllexport)
#endif

class F3EIApplication
{
public:
	virtual void OnInit() = 0;
	virtual void OnUpdate() = 0;
	virtual void OnExit() = 0;
};

#endif