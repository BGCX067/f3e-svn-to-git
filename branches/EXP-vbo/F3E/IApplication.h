#ifndef IApplication_H
#define IApplication_H

class IApplication
{
public:
	virtual void OnInit() = 0;
	virtual void OnUpdate() = 0;
	virtual void OnExit() = 0;
};

#endif