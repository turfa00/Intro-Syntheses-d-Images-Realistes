#include "direct_lighting_integrator.hpp"

namespace RT_ISICG
{
	Vec3f DirectLightingIntegrator::Li( const Scene & p_scene,
								 const Ray &   p_ray,
								 const float   p_tMin,
								 const float   p_tMax ) const
	{
		HitRecord hitRecord;
		Vec3f	  color = VEC3F_ZERO;
		if ( p_scene.intersect( p_ray, p_tMin, p_tMax, hitRecord ) )
		{
			Vec3f normal	   = hitRecord._normal;
			Vec3f rayDirection = p_ray.getDirection();
			float angle		   = glm::max( glm::dot( -rayDirection, normal ), 0.f );
			//std::cout << "here:" << p_scene.getLights().size() << std::endl;
			color = hitRecord._object->getMaterial()->getFlatColor() * angle;
			for ( int i = 0; i < p_scene.getLights().size(); i++ )
			{
				color += _directLighting( p_scene.getLights().at( i ), hitRecord );
			}
			return color;
			/// TODO ! cos theta...
			/* Vec3f normal = hitRecord._normal;
			Vec3f rayDirection = p_ray.getDirection();

			float angle = glm::max( glm::dot( -rayDirection, normal ), 0.f );
			return hitRecord._object->getMaterial()->getFlatColor() * angle;*/
		}
		else { return _backgroundColor; }
	}

		Vec3f DirectLightingIntegrator::_directLighting( const BaseLight * light, const HitRecord hitRecord ) const
	{
		LightSample lightSample	 = light->sample( hitRecord._point );
		Vec3f	  normal	   = hitRecord._normal;
		
		float cosTheta = glm::max(glm::dot(hitRecord._normal, lightSample._direction), 0.f);
		//float cosTheta = glm::max( glm::dot( lightSample._direction, hitRecord._normal ), 0.f );
		Vec3f color = hitRecord._object->getMaterial()->getFlatColor() * lightSample._radiance * cosTheta;
		return color;
	}

} // namespace RT_ISICG
