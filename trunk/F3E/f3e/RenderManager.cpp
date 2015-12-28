
#include "RenderManager.h"

RenderManager::RenderManager(void)
{
}

RenderManager::~RenderManager(void)
{
}

void RenderManager::addSphere( f3m::Vector3f point, f3::F32 radius )
{
	Sphere sphere;
	sphere.position = point;
	sphere.radius = radius;

	spheres.insert(spheres.begin(), sphere);
}

void RenderManager::addPoint( f3m::Vector3f point )
{
	points.insert(points.begin(), point);
}

void RenderManager::addLine( f3m::Vector3f start, f3m::Vector3f end )
{
	Line line;
	line.point1 = start;
	line.point2 = end;

	lines.insert(lines.begin(), line);
}


void RenderManager::render()
{

}