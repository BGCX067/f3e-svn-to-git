#ifndef RenderManager_h__
#define RenderManager_h__


#include <f3math/Vector.h>
#include <f3base/Common.h>
#include <vector>

class RenderManager
{
	struct Line
	{
		f3m::Vector3f point1;
		f3m::Vector3f point2;
	};

	typedef  f3m::Vector3f Point;

	struct Sphere
	{
		f3m::Vector3f position;
		f3::F32 radius;
	};

	std::vector<Line> lines;
	std::vector<Point> points;
	std::vector<Sphere> spheres;

public:
	RenderManager(void);
	~RenderManager(void);
	void addLine(f3m::Vector3f start, f3m::Vector3f end);
	void addPoint(f3m::Vector3f point);
	void addSphere(f3m::Vector3f point, f3::F32 radius);
	void render();
};
#endif // RenderManager_h__
