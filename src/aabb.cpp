#include "aabb.hpp"

namespace RT_ISICG
{
	bool AABB::intersect( const Ray & p_ray, const float p_tMin, const float p_tMax ) const
	{
		Vec3f rayOrigin = p_ray.getOrigin();
		Vec3f rayDirection = p_ray.getDirection();
		Vec3f tMin		   = ( _min - rayOrigin ) / rayDirection;
		Vec3f tMax		   = ( _max - rayOrigin ) / rayDirection;
		Vec3f t1	= min( tMin, tMax );
		Vec3f t2	= max( tMin, tMax );
		float tNear = max( max( t1.x, t1.y ), t1.z );
		float tFar	= min( min( t2.x, t2.y ), t2.z );

		return vec2( tNear, tFar );
		return false;
	}
} // namespace RT_ISICG
