#ifndef Animator_h__
#define Animator_h__

#include <f3base/Common.h>
#include "MoveAnimation.h"

namespace f3
{	
	class DLL Animator
	{
		float _elapsed;
		float _duration;
		bool _running;
		f3::I32 _id;
		MoveAnimation& _animation;

	public:
		Animator(MoveAnimation& animation);
		~Animator(void);
		void update(float delta);
		void start();
		void stop();
		void pause();
	};
}
#endif // Animator_h__
