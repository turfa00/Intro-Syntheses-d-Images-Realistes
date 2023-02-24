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
			//Shadows
			Vec3f normal	   = hitRecord._normal;
			Vec3f rayDirection = p_ray.getDirection();

			float angle = glm::max( glm::dot( -rayDirection, normal ), 0.f );

			for (int i = 0; i < p_scene.getLights().size(); i++) {
				HitRecord hitRecordShadow;
				//BaseLight light				 = p_scene.getLights().at( i );
				Vec3f	  lightPoint		 = Vec3f(1, 10, 1); //To work on later
				Vec3f	  shadowRayDirection = glm::normalize( lightPoint - hitRecord._point );
				Ray		  shadowRay( hitRecord._point, shadowRayDirection );
				shadowRay.offset( normal );
				color = hitRecord._object->getMaterial()->getFlatColor() * angle;
				if (p_scene.intersect(shadowRay, p_tMin, p_tMax, hitRecordShadow)) { 
					color = BLACK;
				}
				else { 
					color += _directLighting( p_scene.getLights().at( i ), hitRecord );
				}
			}

			return color;

			//color		= hitRecord._object->getMaterial()->getFlatColor() * angle;

			//Original
			/* Vec3f normal		= hitRecord._normal;
			Vec3f rayDirection = p_ray.getDirection();

			float angle		   = glm::max( glm::dot( -rayDirection, normal ), 0.f );
			color = hitRecord._object->getMaterial()->getFlatColor() * angle;
			for ( int i = 0; i < p_scene.getLights().size(); i++ )
			{
				HitRecord hitRecordShadow;
				Ray rayShadow( hitRecord._point, -rayDirection );
				Vec3f objectPoint = p_ray.getOrigin();
				color += _directLighting( p_scene.getLights().at( i ), hitRecord );
				if ( p_scene.intersect( p_ray, p_tMin, p_tMax, hitRecord ) )
				{ 
					//if ( hitRecordShadow._object->getMaterial()->shade )
					//std::cout << "here" << std::endl;
					//color += Vec3f( 0.f );
				}
				else { color += _directLighting( p_scene.getLights().at( i ), hitRecord );
				}
			}
			return color;*/

			//First
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
		Vec3f color = hitRecord._object->getMaterial()->getFlatColor() * lightSample._radiance * cosTheta;
		return color;
	}

} // namespace RT_ISICG
