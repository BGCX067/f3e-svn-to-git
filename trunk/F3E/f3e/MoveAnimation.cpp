#include "MoveAnimation.h"

f3::MoveAnimation::MoveAnimation(const f3m::Vector3f& start, const f3m::Vector3f& end, f3m::Vector3f& prop) : _start(start), _end(end), _prop(prop)
{
}

f3::MoveAnimation::~MoveAnimation(void)
{
}

void f3::MoveAnimation::update( float percent )
{
	f3m::Vector3f diff = (_end - _start) * percent;
	_prop = diff;
}