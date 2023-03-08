#include "ray_cast_integrator.hpp"

namespace RT_ISICG
{
	Vec3f RayCastIntegrator::Li( const Scene & p_scene,
								 const Ray &   p_ray,
								 const float   p_tMin,
								 const float   p_tMax ) const
	{
		HitRecord hitRecord;
		if ( p_scene.intersect( p_ray, p_tMin, p_tMax, hitRecord ) )
		{
			/// TODO ! cos theta...
			Vec3f normal = hitRecord._normal;
			Vec3f rayDirection = p_ray.getDirection();

			float angle = glm::max(glm::dot( -rayDirection, normal ), 0.f);
			//float angle = glm::max(glm::dot( -rayDirection, normal ), 0.f);
			return hitRecord._object->getMaterial()->getFlatColor() * angle;
		}
		else
		{
			return _backgroundColor;
		}
	}
} // namespace RT_ISICG
