#include "sphere_geometry.hpp"

namespace RT_ISICG
{
	bool SphereGeometry::intersect( const Ray & p_ray, float & p_t1, float & p_t2 ) const
	{
		/// TODO !
		Vec3f rayOrigin = p_ray.getOrigin();
		Vec3f rayDirection = p_ray.getDirection();
		Vec3f center	   = getCenter();
		float radius	   = getRadius();

		Vec3f oc		   = rayOrigin - center;
		//TD5 FIG
		//float a = glm::dot( rayDirection, rayDirection );
		float b	= 2.0f * glm::dot(oc, rayDirection );
		float c = glm::dot( oc, oc ) - (radius * radius);
		
		float delta = b * b - 4 * c;
		if ( delta >= 0 ) { 
			p_t1 = ( -b - sqrt( delta ) ) / 2;
			p_t2 = ( -b + sqrt( delta ) ) / 2;
			if ( p_t1 > p_t2 )
			{
				std::swap( p_t1, p_t2 );
			}
			return true;
		}

		return false;
	}

} // namespace RT_ISICG
