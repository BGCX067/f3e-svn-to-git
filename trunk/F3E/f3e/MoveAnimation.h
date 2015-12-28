#ifndef MoveAnimation_h__
#define MoveAnimation_h__

#include <f3base/Common.h>
#include <f3math/Vector.h>

namespace f3
{
	class DLL MoveAnimation
	{
		const f3m::Vector3f& _start;
		const f3m::Vector3f& _end;
		f3m::Vector3f& _prop;
		void (*_ptr)(f3m::Vector3f);

	public:
		MoveAnimation(const f3m::Vector3f& start, const f3m::Vector3f& end, f3m::Vector3f& prop);
		~MoveAnimation(void);
		void update(float percent);
	};
}
#endif // MoveAnimation_h__
