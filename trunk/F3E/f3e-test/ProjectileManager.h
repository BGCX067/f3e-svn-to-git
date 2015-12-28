
#ifndef ProjectileManager_h__
#define ProjectileManager_h__

#include <f3base/Common.h>
#include <f3math/Vector.h>
#include <vector>

class Projectile
{
public:
	f3m::Vector3f _position;
	f3m::Vector3f _direction;
	f3::F32 _velocity;
};
class ProjectileManager
{
	std::vector<Projectile> _projectiles;

public:
	ProjectileManager(void);
	~ProjectileManager(void);

	void add(const Projectile& projectile);
	void update(f3::F32 delta);
};

extern ProjectileManager projectiles;

#endif // ProjectileManager_h__