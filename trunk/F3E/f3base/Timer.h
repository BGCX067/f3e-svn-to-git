#ifndef Timer_h__
#define Timer_h__

#include "Common.h"
#include <windows.h>

namespace f3
{
	class Timer
	{
		LARGE_INTEGER frequency;        // ticks per second
		LARGE_INTEGER t1, t2;           // ticks
	protected:
		float elapsedTime;
		float targetfps;

	public:
		Timer(void);
		~Timer(void);
		virtual void start();
		virtual void stop();
		virtual float elapsed();
	};
}
#endif // Timer_h__