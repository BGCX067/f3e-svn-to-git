#include "Animator.h"
#include <sstream>

f3::Animator::Animator(MoveAnimation& animation) : _elapsed(0.0f), _animation(animation),  _duration(5000)
{
	_id = 0;
}

f3::Animator::~Animator(void)
{
}

void f3::Animator::update( float delta )
{
	_elapsed += delta;
	
	if (_elapsed >= _duration)
		_elapsed = 0.0f;

	float percent = _elapsed/_duration;
	_animation.update(percent);

	//std::ostringstream os;
	//os << "animation percent: " << percent;
	//util::log.info(os.str());
}

void f3::Animator::start()
{
	_running = true;

	std::ostringstream os;
	os << "Timer #" << _id << " start";
	f3::util::log.info(os.str());
}

void f3::Animator::stop()
{
	_running = false;
	_elapsed = 0.0f;
}

void f3::Animator::pause()
{
	_running = false;
}