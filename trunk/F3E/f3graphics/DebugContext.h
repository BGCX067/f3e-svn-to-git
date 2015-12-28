#pragma once
#ifndef DebugContext_h__
#define DebugContext_h__

#include <f3base/Common.h>
#include <f3math/Vector.h>
#include <vector>
#include <f3base/ColorRGBA.h>

namespace f3
{
	namespace graphics
	{
		typedef  f3m::Vector3f Point;

		struct Sphere
		{
			f3m::Vector3f position;
			f3::F32 radius;
		};

		struct RenderString
		{
			f3m::Vector3f position;
			f3::string text;
			f3u::ColorRGBA color;
		};

		class DebugContext
		{

			
		public:
			DebugContext(void);
			~DebugContext(void);
			
			void addText(f3m::Vector3f position, std::string text, f3u::ColorRGBA color = f3u::ColorRGBA(1,1,1));
			void addLine(f3m::Vector3f start, f3m::Vector3f end);
			void addPoint(f3m::Vector3f point);
			void addSphere(f3m::Vector3f point, f3::F32 radius);
			void DebugContext::clear();
			std::vector<f3m::Vector3f> lines;
			std::vector<Point> points;
			std::vector<Sphere> spheres;
			std::vector<RenderString> strings;
		};
	}
}
#endif // DebugContext_h__

