#include "implicit_surface.hpp"

namespace RT_ISICG
{
	bool ImplicitSurface::intersect( const Ray & p_ray,
									 const float p_tMin,
									 const float p_tMax,
									 HitRecord & p_hitRecord ) const
	{
		float pos = p_tMin; //Position sur le rayon
		float step; //Distance de pas sur le rayon
		Vec3f rayPoint; //Le point dans l'espace ou se situe le pos initial
		while ( pos < p_tMax ) {
			rayPoint = p_ray.pointAtT( pos );
			step	= _sdf( rayPoint );
			//step = 1.f;
			pos += step;
			if ( step < _minDistance )
			{ 
				p_hitRecord._point	= p_ray.pointAtT( pos );
				p_hitRecord._normal = _evaluateNormal( p_hitRecord._point );
				p_hitRecord.faceNormal( p_ray.getDirection() );
				p_hitRecord._distance = step;
				p_hitRecord._object	  = this;
				return true;
			}
		}
		return false;
	}

	bool ImplicitSurface::intersectAny( const Ray & p_ray, const float p_tMin, const float p_tMax ) const
	{

		float pos = p_tMin;
		float step;
		Vec3f rayPoint;
		while ( pos < p_tMax )
		{
			rayPoint = p_ray.pointAtT( pos );
			step	 = _sdf( rayPoint );
			pos += step;
			if ( step < _minDistance )
			{
				return true;
			}
		}

		return false;
	}
} // namespace RT_ISICG
