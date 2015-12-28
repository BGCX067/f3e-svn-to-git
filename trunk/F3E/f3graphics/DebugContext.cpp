#include "DebugContext.h"
#include <f3base\ColorRGBA.h>

namespace f3
{
	namespace graphics
	{
		DebugContext::DebugContext(void)
		{
		}


		DebugContext::~DebugContext(void)
		{
		}

		void DebugContext::addSphere( f3m::Vector3f point, f3::F32 radius )
		{
			Sphere sphere;
			sphere.position = point;
			sphere.radius = radius;

			spheres.insert(spheres.begin(), sphere);
		}

		void DebugContext::addPoint( f3m::Vector3f point )
		{
			points.insert(points.begin(), point);
		}

		void DebugContext::addLine( f3m::Vector3f start, f3m::Vector3f end )
		{
			lines.insert(lines.end(), start);
			lines.insert(lines.end(), end);
		}

		void DebugContext::addText( f3m::Vector3f position, std::string text, f3u::ColorRGBA color )
		{
			RenderString rs;
			rs.color = color;
			rs.position = position;
			rs.text = text;
			strings.push_back(rs);
		}

		void DebugContext::clear()
		{
			points.clear();
			lines.clear();
			strings.clear();
			spheres.clear();
		}

		DebugContext debug;
	}
}