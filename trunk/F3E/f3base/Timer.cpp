#include "Stdafx.h"

#include "Timer.h"
#include <iostream>
#include <sstream>

namespace f3
{
	Timer::Timer(void)
	{
		targetfps = 100.0f;
		QueryPerformanceFrequency(&frequency);
	}
	
	Timer::~Timer(void)
	{
	}

	void Timer::start()
	{		
		QueryPerformanceCounter(&t1);
	}

	void Timer::stop()
	{
		QueryPerformanceCounter(&t2);
		elapsedTime = (t2.QuadPart - t1.QuadPart)*1000.0f  / frequency.QuadPart;
	}

	float Timer::elapsed()
	{
		return elapsedTime;
	}
}
