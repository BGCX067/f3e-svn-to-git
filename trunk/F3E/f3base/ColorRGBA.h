#ifndef ColorRGBA_h__
#define ColorRGBA_h__

namespace f3
{
	namespace util
	{
		class ColorRGBA
		{
		public:
			float r, g, b, a;

			ColorRGBA(float r = 0.0f, float g= 0.0f, float b = 0.0f, float a = 1.0f) : r(r), g(g), b(b), a(a) {}; 
		};
	}
}

#endif // ColorRGBA_h__
