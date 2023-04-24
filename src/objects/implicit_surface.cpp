#include "implicit_surface.hpp"

namespace RT_ISICG
{
	bool ImplicitSurface::intersect( const Ray & p_ray,
									 const float p_tMin,
									 const float p_tMax,
									 HitRecord & p_hitRecord ) const
	{
		float t_depth = p_tMin, distance;
		Vec3f p_depth;

		while ( t_depth < p_tMax )
		{
			p_depth	 = p_ray.pointAtT( t_depth );
			distance = _sdf( p_depth );
			t_depth += distance;

			if ( distance < _minDistance )
			{
				p_hitRecord._point	= p_ray.pointAtT( t_depth );
				p_hitRecord._normal = _evaluateNormal( p_hitRecord._point );
				p_hitRecord.faceNormal( p_ray.getDirection() );
				p_hitRecord._distance = t_depth;
				p_hitRecord._object	  = this;
				return true;
			}
		}

		return false;
	}

	bool ImplicitSurface::intersectAny( const Ray & p_ray, const float p_tMin, const float p_tMax ) const
	{
		float t_depth = p_tMin, distance;
		Vec3f p_depth;

		while ( t_depth < p_tMax )
		{
			p_depth	 = p_ray.pointAtT( t_depth );
			distance = _sdf( p_depth );
			t_depth += distance;
			if ( distance < _minDistance ) return true;
		}

		return false;
	}
} // namespace RT_ISICG
