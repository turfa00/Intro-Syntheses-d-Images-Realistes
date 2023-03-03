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
			//Shadows
			Vec3f normal	   = hitRecord._normal;
			Vec3f rayDirection = p_ray.getDirection();

			float angle = glm::max( glm::dot( -rayDirection, normal ), 0.f );

			for (int i = 0; i < p_scene.getLights().size(); i++) {
				Vec3f lightPoint = Vec3f( 1, 10, 2 ); // To work on later
				if ( p_scene.getLights().at(i)->getIsSurface())
				{
					LightSample lightSample = p_scene.getLights().at( i )->sample( hitRecord._point );
					HitRecord hitRecordShadow;
					// QuadLight light( p_scene.getLights().at(i) );
					Vec3f shadowRayDirection = glm::normalize( lightPoint - hitRecord._point );

					//Ray	  shadowRay( hitRecord._point, shadowRayDirection );
					Ray	  shadowRay( hitRecord._point, lightSample._direction );
					shadowRay.offset( normal );
					//color = hitRecord._object->getMaterial()->getFlatColor() * angle;
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
					
					//color = Vec3f( glm::max( 0.f, color.x / 4 ), glm::max( 0.f, color.y / 4 ), glm::max( 0.f, color.z / 4 ) ); 
					color /= _nbLightSamples;

				}
				else { 
					HitRecord hitRecordShadow;
					// QuadLight light( p_scene.getLights().at(i) );
					Vec3f shadowRayDirection = glm::normalize( lightPoint - hitRecord._point );
					Ray	  shadowRay( hitRecord._point, shadowRayDirection );
					shadowRay.offset( normal );
					color = hitRecord._object->getMaterial()->getFlatColor() * angle;
					if ( p_scene.intersectAny( shadowRay, p_tMin, p_tMax ) ) { 
						color = BLACK; 
					}
					else {
						color += _directLighting( p_scene.getLights().at( i ), hitRecord ); 
					}
				}


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




				//Original
				/* if ( p_scene.intersectAny( shadowRay, p_tMin, p_tMax ) )
				{ 
					color = BLACK;
					//for (int j = 0; j < _nbLightSamples; j++) {
						//Li( p_scene, shadowRay, p_tMin, p_tMax );
					//}
				}
				else { 
					color += _directLighting( p_scene.getLights().at( i ), hitRecord );
				}*/
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
	//Vec3f DirectLightingIntegrator::_directLighting( const QuadLight * light, const HitRecord hitRecord ) const
	{
		LightSample lightSample	 = light->sample( hitRecord._point );
		Vec3f	  normal	   = hitRecord._normal;
		
		float cosTheta = glm::max(glm::dot(hitRecord._normal, lightSample._direction), 0.f);
		Vec3f color = hitRecord._object->getMaterial()->getFlatColor() * lightSample._radiance * cosTheta;
		return color;
	}

} // namespace RT_ISICG
