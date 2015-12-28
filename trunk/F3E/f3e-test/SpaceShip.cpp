#include "SpaceShip.h"

#include <f3math/Matrix.h>
#include <f3base/Common.h>
#include <f3base/Timer.h>
#include <f3graphics/DebugContext.h>
#include <f3scene/Graph.h>
#include "ProjectileManager.h"

SpaceShip::SpaceShip(void)
{
	_position._x = 0.0f;
	_position._y = 0.0f;
	_position._z = 0.0f;

	_orientation._x = 1.000f;
	_orientation._y = 0.0f;
	_orientation._z = 0.0f;

	_forwardforce = f3m::Vector3f(0,0,0);
	_speed = 1.000f; // 1 unit per second
	_sidethrottle = 0.0f;
	_throttle = 0.0f;
	_sidespeed1 = 0.0f;
	_sidespeed2 = 0.0f;
}

SpaceShip::~SpaceShip(void)
{
}


f3m::Vector3f SpaceShip::position() 
{ 
	return _position; 
}

void SpaceShip::throttle(float percent) 
{
	_throttle = percent; 
}

void SpaceShip::steer(float angle) 
{
	_steer = angle;
}

void SpaceShip::fire()
{	
	float firerate = 200.0f;
	static float lastshot = 0.0f;

	if (lastshot > firerate)
	{

	Projectile p;
	p._direction = _orientation;
	p._position = _position;
	p._velocity = 1.0f;
	projectiles.add(p);
		lastshot -=firerate;
	}
	lastshot += f3u::timer.elapsed();

	std::ostringstream os;
	os <<  "_s:" << lastshot;

	f3g::debug.addText(f3m::Vector3f(0,1,0), os.str());
}

float caacceleration(float speed)
{
	float a = 0.001f;
	return a / ((speed*speed) + 0.001f);
}

void SpaceShip::update(float delta) 
{

// steering
	static float rot = 0.0f;
	rot += _steer * delta;

	f3m::Matrix4f rotation = f3m::Matrix4f::rotationZ(rot);
	_angle = rot;
	f3m::Vector3f orientation = f3m::multiply(f3m::Vector3f(0,1,0), rotation);

	float max_speed = 10.00f;
	static float speed = 0.0f;
	float friction = 0.0005f;
	float acceleration = caacceleration(speed);

	speed += acceleration * delta * (_throttle/100.0f);
	
	if (speed > friction)
		speed -= friction * delta;

	//if (speed >= max_speed)
	//	speed = max_speed;

	
	std::ostringstream os2;
	os2 << speed << "\n";
	os2 << acceleration << "\n";
	f3g::debug.addText(f3m::Vector3f(0,2,0), os2.str());




	_position += orientation*(speed/1000.0f);



	//f3s::graph.camera()->position()._x = _position._x;
	//f3s::graph.camera()->position()._y = _position._y;

	forceBounds();


	
	f3::F32 offset = 0.5f;
	f3::F32 offset2 = 0.15f;


	f3m::Vector3f off = f3m::Vector3f::cross(orientation, f3m::Vector3f(0,0,1));

	// draw ship
	f3g::debug.addLine(_position-off*offset2, _position+orientation*offset);
	f3g::debug.addLine(_position+off*offset2, _position+orientation*offset);
	f3g::debug.addLine(_position+off*offset2, _position-off*offset2);
}

void SpaceShip::forceBounds()
{
	float size = 10.0f;
	//top
	f3g::debug.addLine(f3m::Vector3f(size,size,0), f3m::Vector3f(-size,size,0));
	//bottom
	f3g::debug.addLine(f3m::Vector3f(-size,-size,0), f3m::Vector3f(size,-size,0));
	// right
	f3g::debug.addLine(f3m::Vector3f(size,size,0), f3m::Vector3f(size,-size,0));
	// left
	f3g::debug.addLine(f3m::Vector3f(-size,size,0), f3m::Vector3f(-size,-size,0));

	if (_position._x > size || _position._x < -size)
	{
		if (_position._x > 0)
			_position._x = size;
		else
			_position._x = -size;
	}
	if (_position._y > size || _position._y < -size)
	{
		if (_position._y > 0)
			_position._y = size;
		else
			_position._y = -size;
	}
}

void SpaceShip::strafe( float percent )
{
	_sidethrottle = percent; // add minus for direction
}
