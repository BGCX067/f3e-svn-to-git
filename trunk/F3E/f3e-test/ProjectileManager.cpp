#include "ProjectileManager.h"
#include <f3base\Common.h>
#include <f3graphics\DebugContext.h>
ProjectileManager projectiles;

ProjectileManager::ProjectileManager(void)
{
}


ProjectileManager::~ProjectileManager(void)
{
}

void ProjectileManager::add( const Projectile& projectile )
{

	_projectiles.push_back(projectile);
}

void ProjectileManager::update( f3::F32 delta )
{
	std::vector<Projectile>::iterator itr = _projectiles.begin();
	//

	while (itr != _projectiles.end())
	{
		f3m::Vector3f& _position = itr->_position;
		float size = 9.0f;

		itr->_position += itr->_direction*(itr->_velocity/100.0f) * delta;
		f3g::debug.addLine(itr->_position, itr->_position+(itr->_direction*0.1f));
		

		if (_position._x > size || _position._x < -size)
		{
			itr = _projectiles.erase(itr);			
		}
		else if (_position._y > size || _position._y < -size)
		{
			itr = _projectiles.erase(itr);
		}
		else
			++itr;
	}
}
