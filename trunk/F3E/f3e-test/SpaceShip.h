#ifndef SpaceShip_h__
#define SpaceShip_h__

#include <f3base/Common.h>
#include <f3math/Vector.h>

class SpaceShip
{
public:
	SpaceShip(void);
	~SpaceShip(void);
	f3m::Vector3f _position;
	f3m::Vector3f _orientation;
	f3m::Vector3f _engines;
	f3m::Vector3f _force;
	f3m::Vector3f _forwardforce;
	f3::F32 _speed;
	f3::F32 _throttle;
	f3::F32 _sidethrottle;
	f3::F32 _sidespeed1;
	f3::F32 _sidespeed2;
	f3::F32 _steer;
	f3::F32 _angle;
	f3::F32 _lastshot;

	f3m::Vector3f position();
	void throttle(float percent);
	void strafe(float percent);
	void update(float delta);
	void steer(float percent);
	void forceBounds();
	void fire();
};


#endif // SpaceShip_h__