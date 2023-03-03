#include "direct_lighting_integrator.hpp"
#include "lights/base_light.hpp"
#include "lights/quad_light.hpp"

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

			float angle = glm::max( glm::dot( -rayDirection, normal ), 0.f );

			for (int i = 0; i < p_scene.getLights().size(); i++) {
				LightSample lightSample = p_scene.getLights().at( i )->sample( hitRecord._point );
				Ray			shadowRay( hitRecord._point, -lightSample._direction );
				shadowRay.offset( normal );
				color = hitRecord._object->getMaterial()->getFlatColor() * angle;
				if ( p_scene.intersectAny( shadowRay, p_tMin, p_tMax ) ) 
				{ 
					color = BLACK; 
				}
				else 
				{ 
					color += _directLighting( p_scene.getLights().at( i ), hitRecord ); 
				}



				/*
				if ( p_scene.getLights().at(i)->getIsSurface())
				{
					for (int j = 0; j < _nbLightSamples; j++) {
						color += hitRecord._object->getMaterial()->getFlatColor() * angle;
						if ( p_scene.intersectAny( shadowRay, p_tMin, p_tMax ) )
						{
							color = BLACK;
						}
						else {
							color += _directLighting( p_scene.getLights().at( i ), hitRecord );
						}

					}
					color /= _nbLightSamples;

				}
				else {
					if ( p_scene.intersectAny( shadowRay, p_tMin, p_tMax ) ) { 
						color = BLACK; 
					}
					else {
						color += _directLighting( p_scene.getLights().at( i ), hitRecord ); 
					}
				}*/


				/* HitRecord hitRecordShadow;
				Vec3f	  lightPoint		 = Vec3f(1, 10, 2); //To work on later
				Vec3f	  shadowRayDirection = glm::normalize( lightPoint - hitRecord._point );
				Ray		  shadowRay( hitRecord._point, shadowRayDirection );
				shadowRay.offset( normal );
				color = hitRecord._object->getMaterial()->getFlatColor() * angle;

				if ( hitRecordShadow._object != nullptr )
				{ 
					//color += _directLighting( p_scene.getLights().at( i ), hitRecord );
					for (int j = 0; j < _nbLightSamples; j++) {
						if (p_scene.intersectAny(shadowRay, p_tMin, p_tMax)) { 
							//color = BLACK;
						}
						else { 
							color += _directLighting( p_scene.getLights().at( i ), hitRecord );
						}
					}
				}*/
			}
			
			return color;
		}
		else { return _backgroundColor; }
	}

	Vec3f DirectLightingIntegrator::_directLighting( const BaseLight * light, const HitRecord hitRecord ) const
	{
		Vec3f color = VEC3F_ZERO;
		if ( light->getIsSurface() ) 
		{
			for (int i = 0; i < _nbLightSamples; i++) {
				LightSample lightSample = light->sample( hitRecord._point );
				Vec3f		normal		= hitRecord._normal;
				float cosTheta = glm::max( glm::dot( hitRecord._normal, lightSample._direction ), 0.f );
				color		   += hitRecord._object->getMaterial()->getFlatColor() * lightSample._radiance * cosTheta;
			}
			color /= _nbLightSamples;
		}
		else {
			LightSample lightSample = light->sample( hitRecord._point );
			Vec3f		normal		= hitRecord._normal;
			float		cosTheta	= glm::max( glm::dot( hitRecord._normal, lightSample._direction ), 0.f );
			color += hitRecord._object->getMaterial()->getFlatColor() * lightSample._radiance * cosTheta;
		}
		return color;
	}

} // namespace RT_ISICG
