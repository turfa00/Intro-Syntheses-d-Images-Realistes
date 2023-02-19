#include "plane.hpp"

namespace RT_ISICG 
{
	bool Plane::intersect( const Ray & p_ray, const float p_tMin, const float p_tMax, HitRecord & p_hitRecord ) const
	{
		float t1;
		float t2;
		if ( _geometry.intersect( p_ray, t1, t2 ) )
		{
			if ( t1 > p_tMax ) { return false; }				// first intersection too far
			if ( t1 < p_tMin ) { t1 = t2; }						// first intersection too near, check second one
			if ( t1 < p_tMin || t1 > p_tMax ) { return false; } // not in range

			// Intersection found, fill p_hitRecord.
			p_hitRecord._point	= p_ray.pointAtT( t1 );
			//p_hitRecord._normal = _geometry.computeNormal( p_hitRecord._point );
			p_hitRecord._normal = _geometry.getNormal();
			p_hitRecord.faceNormal( p_ray.getDirection() );
			p_hitRecord._distance = t1;
			p_hitRecord._object	  = this;

			return true;
		}
		return false;
	}
}