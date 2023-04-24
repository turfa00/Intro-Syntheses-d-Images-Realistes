#include "whitted_integrator.hpp"
#include "lights/base_light.hpp"
#include "lights/quad_light.hpp"
#include <materials/matte_material.hpp>
#include <materials/plastic_material.hpp>

namespace RT_ISICG
{
	Vec3f WhittedIntegrator::Li( const Scene & p_scene,
								 const Ray &   p_ray,
								 const float   p_tMin,
								 const float   p_tMax ) const
	{
		return trace( p_scene, p_ray, p_tMin, p_tMax, _nbBounce );
	}

	Vec3f WhittedIntegrator::_directLighting( const Scene &	p_scene, const Ray & p_ray, const float	p_tMin, const float p_tMax ) const
	{
		HitRecord hitRecord;
		Vec3f	  color = BLACK;
		Vec3f	  _fr	= VEC3F_ZERO;

		Vec3f		normal		= hitRecord._normal;
		//float		cosTheta	= glm::max( glm::dot( lightSample._direction, hitRecord._normal ), 0.f );
		if ( p_scene.intersect( p_ray, p_tMin, p_tMax, hitRecord ) )
		{
			for ( int i = 0; i < p_scene.getLights().size(); i++ )
			{
				LightSample lightSample = p_scene.getLights().at( i )->sample( hitRecord._point );
				Ray			shadowRay( hitRecord._point, lightSample._direction );
				shadowRay.offset( hitRecord._normal );

				_fr = hitRecord._object->getMaterial()->shade( p_ray, hitRecord, lightSample );

				if ( p_scene.getLights().at( i )->getIsSurface() )
				{

					for ( int j = 0; j < _nbLightSamples; j++ )
					{
						lightSample = p_scene.getLights().at( i )->sample( hitRecord._point );
						Ray shadowRay( hitRecord._point, lightSample._direction );
						shadowRay.offset( hitRecord._normal );

						_fr += hitRecord._object->getMaterial()->shade( p_ray, hitRecord, lightSample );

						if ( !p_scene.intersectAny( shadowRay, p_tMin, lightSample._distance ) )
						{
							/// TODO: shading
							//color += _directLighting( p_scene.getLights().at( i ), hitRecord ) * _fr;
							color += hitRecord._object->getMaterial()->shade( p_ray, hitRecord, lightSample );
						}
					}
					color /= _nbLightSamples;
					_fr /= _nbLightSamples;
				}
				else
				{
					if ( !p_scene.intersectAny( shadowRay, p_tMin, lightSample._distance ) )
					{
						//color += _directLighting( p_scene.getLights().at( i ), hitRecord ) * _fr;
						color += hitRecord._object->getMaterial()->shade( p_ray, hitRecord, lightSample );
						_fr += hitRecord._object->getMaterial()->shade( p_ray, hitRecord, lightSample );
					}
				}
			}
			return _fr;
		}
		else { return _backgroundColor; }
	}

	Vec3f WhittedIntegrator::trace( const Scene & p_scene, const Ray & p_ray, const float p_tMin, const float p_tMax, int p_nbounces ) const
	{
		HitRecord hitRecord;
		if (p_scene.intersect(p_ray, p_tMin, p_tMax, hitRecord)) {
			if ( p_nbounces == 0 ) { return _directLighting( p_scene, p_ray, p_tMin, p_tMax ); }

			if ( hitRecord._object->getMaterial()->isMirror() )
			{
				Ray reflectRay = Ray( hitRecord._point, glm::reflect( p_ray.getDirection(), hitRecord._normal ) );
				reflectRay.offset( hitRecord._normal );
				return trace( p_scene, reflectRay, p_tMin, p_tMax, p_nbounces - 1);
			}

			else { return _directLighting( p_scene, p_ray, p_tMin, p_tMax );
			}
		}

		return _backgroundColor;
	}

} // namespace RT_ISICG