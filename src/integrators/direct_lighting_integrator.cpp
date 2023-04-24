#include "direct_lighting_integrator.hpp"
#include "lights/base_light.hpp"
#include "lights/quad_light.hpp"
#include <materials/matte_material.hpp>
#include <materials/plastic_material.hpp>

namespace RT_ISICG
{
	Vec3f DirectLightingIntegrator::Li( const Scene & p_scene,
								 const Ray &   p_ray,
								 const float   p_tMin,
								 const float   p_tMax ) const
	{
		HitRecord hitRecord;
		Vec3f	  color = BLACK;
		Vec3f	  _fr	= VEC3F_ZERO;
		
		if ( p_scene.intersect( p_ray, p_tMin, p_tMax, hitRecord ) ) 
		{
			for ( int i = 0; i < p_scene.getLights().size(); i++ ) 
			{
				LightSample lightSample = p_scene.getLights().at( i )->sample( hitRecord._point );
				Ray			shadowRay( hitRecord._point, lightSample._direction );
				shadowRay.offset( hitRecord._normal );
				s
				_fr = hitRecord._object->getMaterial()->shade( p_ray, hitRecord, lightSample );

				// TODO: appeler directlighting ici
				// directlighting boucle sur les lumières, pour chaque lance un shadow ray et shade si pas d'intersection
				if ( p_scene.getLights().at( i )->getIsSurface() )
				{
					for (int j = 0; j < _nbLightSamples; j++) {
						lightSample = p_scene.getLights().at( i )->sample( hitRecord._point );
						Ray			shadowRay( hitRecord._point, lightSample._direction );
						shadowRay.offset( hitRecord._normal );

						_fr = hitRecord._object->getMaterial()->shade( p_ray, hitRecord, lightSample );

						if ( !p_scene.intersectAny( shadowRay, p_tMin, lightSample._distance ) )
						{
							/// TODO: shading
							color += _directLighting( p_scene.getLights().at( i ), hitRecord ) * _fr;
						}
					}
				}
				else {
					if ( !p_scene.intersectAny( shadowRay, p_tMin, lightSample._distance ) )
					{
						color += _directLighting( p_scene.getLights().at( i ), hitRecord ) * _fr;
					}
				}
				
			}
			return color;
		}
		else 
		{ 
			return _backgroundColor;
		}
		
		
	}

	Vec3f DirectLightingIntegrator::_directLighting( const BaseLight * light, const HitRecord hitRecord ) const
	{
		Vec3f color = VEC3F_ZERO;

		LightSample lightSample = light->sample( hitRecord._point );
		Vec3f		normal		= hitRecord._normal;
		float		cosTheta	= glm::max( glm::dot( lightSample._direction, hitRecord._normal ), 0.f );
		

		if ( light->getIsSurface() ) 
		{
			for (int i = 0; i < _nbLightSamples; i++) {
				color	+= hitRecord._object->getMaterial()->getFlatColor() * lightSample._radiance * cosTheta;
			}
			color /= _nbLightSamples;
		}
		else {
			
			color = hitRecord._object->getMaterial()->getFlatColor() * lightSample._radiance * cosTheta;
		}
		//color = hitRecord._object->getMaterial()->getFlatColor() * lightSample._radiance * cosTheta;
		return color;
	}

} // namespace RT_ISICG