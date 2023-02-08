#include "sphere_geometry.hpp"

namespace RT_ISICG
{
	bool SphereGeometry::intersect( const Ray & p_ray, float & p_t1, float & p_t2 ) const
	{
		/// TODO !
		bool  intersect	   = false;
		Vec3f rayOrigin = p_ray.getOrigin();
		Vec3f rayDirection = p_ray.getDirection();
		Vec3f center	   = getCenter();
		float radius	   = getRadius();

		Vec3f oc		   = rayOrigin - center;
		//glm::
		//TD5 FIG
		float b	= 2 * glm::dot(oc, rayDirection );
		float c = glm::dot( oc, oc ) - glm::pow(radius, 2);
		
		float delta = b * b - 4 * c;
		if ( delta >= 0 ) { 
			float t = ( -b - sqrt( delta ) ) / 2;
			if (t >= 0) { 
				intersect = true;
			}
			float t1c = sqrt( ( radius * radius ) - ( delta * delta ) );
			p_t1	  = b - t1c;
			p_t2	  = b + t1c;
			if (p_t2 < p_t1) {
				float temp = p_t1;
				p_t1	   = p_t2;
				p_t2	   = temp; 
			}
		}
		//p_t1 = -1.f;
		//p_t2 = -1.f;

		return intersect;
	}

} // namespace RT_ISICG
