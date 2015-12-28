#ifndef F3EIApplication_H
#define F3EIApplication_H

class F3EIApplication
{
public:
	virtual void OnInit() = 0;
	virtual void OnUpdate() = 0;
	virtual void OnExit() = 0;
};

#endif