#ifndef IWindowListener_h__
#define IWindowListener_h__


class IWindowListener
{
public:
	virtual void onResize(int w, int h) = 0;
	virtual void onDraw() = 0;
	virtual void onDestroy() = 0;
};

#endif // IWindowListener_h__