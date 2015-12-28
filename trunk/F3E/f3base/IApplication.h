#ifndef IApplication_H
#define IApplication_H

class IApplication
{
public:
	virtual void onInit() = 0;
	virtual void onUpdate() = 0;
	virtual void onExit() = 0;
};

#endif