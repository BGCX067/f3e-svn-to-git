
#ifndef FilteredTimer_h__
#define FilteredTimer_h__

#include "Common.h"
#include "Timer.h"

namespace f3
{
	template <int J>
	class DLL FilteredTimer : public Timer
	{
		float cache[J];
		int current;
		float _filteredTimestep;

	public:
		FilteredTimer(void) : Timer()
		{
			current = 0;
			_filteredTimestep = 0.0f;
			memset(&cache, 0, sizeof(float)*J);
		}

		~FilteredTimer(void)
		{
		}

		void stop()
		{
			f3::Timer::stop();
			cache[current] = f3::Timer::elapsed();
			++current;
			if (current == J)
				current = 0;

			float sum = 0.0f;

			for (int i = 0; i < J; i++)
			{
				sum += cache[i];
			}

			_filteredTimestep = sum/J;
		}

		float filteredTimestep()
		{
			return _filteredTimestep;
		}
	};
}
#endif // FilteredTimer_h__
