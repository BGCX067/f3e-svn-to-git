#ifndef MouseState_h__
#define MouseState_h__

#include <f3base/Common.h>

namespace f3
{
	namespace input 
	{

		class MouseState
		{
		public:
			f3::I32 _x;
			f3::I32 _y;
			f3::I32 _z;
			f3::I32 _relX;
			f3::I32 _relY;
			f3::I32 _relZ;
		};
	}
}
#endif // MouseState_h__
