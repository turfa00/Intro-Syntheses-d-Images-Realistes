#include "plane_geometry.hpp"

namespace RT_ISICG
{
	bool PlaneGeometry::intersect( const Ray & p_ray, float & p_t1, float & p_t2 ) const
	{
		Vec3f rayOrigin	   = p_ray.getOrigin();
		Vec3f rayDirection = p_ray.getDirection();
		Vec3f point	   = getPoint();
		Vec3f normal	   = getNormal();

		float den = glm::dot( glm::normalize(normal), glm::normalize(rayDirection ));
		if (den != 0) { 
			Vec3f po = point - rayOrigin;
			p_t1 = glm::dot( po, normal ) / den;
			p_t2 = glm::dot( po, normal ) / den;
			return true;		
		}
		return false;
	}
}