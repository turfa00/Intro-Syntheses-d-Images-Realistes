#include "direct_lighting_integrator.hpp"

namespace RT_ISICG
{
	Vec3f DirectLightingIntegrator::Li( const Scene & p_scene,
								 const Ray &   p_ray,
								 const float   p_tMin,
								 const float   p_tMax ) const
	{
		HitRecord hitRecord;
		if ( p_scene.intersect( p_ray, p_tMin, p_tMax, hitRecord ) )
		{
			Vec3f normal	   = hitRecord._normal;
			Vec3f rayDirection = p_ray.getDirection();
			LightSample lightSample(rayDirection, 1.f, WHITE, 1.f);
			float angle = glm::max( glm::dot( -rayDirection, normal ), 0.f );

			//luminanceFinale += _directLighting( p_scene, p_ray, p_tMin, p_tMax );
			Vec3f color = hitRecord._object->getMaterial()->getFlatColor() * angle;
			//luminanceFinale += Li( p_scene, p_ray, p_tMin, p_tMax );
			//hitRecord._object->getMaterial()->getFlatColor();
			return color;
			//return hitRecord._object->getMaterial()->getFlatColor() * lightSample._radiance * angle;
			/// TODO ! cos theta...
			/* Vec3f normal = hitRecord._normal;
			Vec3f rayDirection = p_ray.getDirection();

			float angle = glm::max( glm::dot( -rayDirection, normal ), 0.f );
			return hitRecord._object->getMaterial()->getFlatColor() * angle;*/
		}
		else { return _backgroundColor; }
	}

		Vec3f DirectLightingIntegrator::_directLighting( const Scene & p_scene, const Ray & p_ray, const float p_tMin, const float p_tMax )
	{
		HitRecord hitRecord;
		Vec3f	  normal	   = hitRecord._normal;
		Vec3f	  rayDirection = p_ray.getDirection();
		float	  angle = glm::max( glm::dot( -rayDirection, normal ), 0.f );

		Vec3f color = hitRecord._object->getMaterial()->getFlatColor() * angle;
		return color;
	}

} // namespace RT_ISICG
