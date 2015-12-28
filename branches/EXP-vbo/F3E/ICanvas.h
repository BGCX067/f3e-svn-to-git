#ifndef ICANVAS_H
#define ICANVAS_H

namespace graphics
{
class ICanvas
{
public:
	virtual void draw() = 0;
	virtual void destroy() = 0;
	virtual void resize(int w, int h) = 0;
};
}
#endif