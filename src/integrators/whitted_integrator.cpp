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
		return trace( p_scene, p_ray, p_tMin, p_tMax, _nbBounce, false );
	}

	Vec3f WhittedIntegrator::_directLighting( const Scene &	p_scene, const Ray & p_ray, const HitRecord & hitRecord, const float p_tMax ) const
	{
		Vec3f	  color = BLACK;
		Vec3f	  _fr	= VEC3F_ZERO;

		Vec3f		normal		= hitRecord._normal;

		for ( int i = 0; i < p_scene.getLights().size(); i++ )
		{
			LightSample lightSample = p_scene.getLights().at( i )->sample( hitRecord._point );
			Ray			shadowRay( hitRecord._point, lightSample._direction );
			shadowRay.offset( hitRecord._normal );

			_fr = hitRecord._object->getMaterial()->shade( p_ray, hitRecord, lightSample );

			float cosTheta = glm::max( 0.f, glm::dot( lightSample._direction, hitRecord._normal ) );
			if ( p_scene.getLights().at( i )->getIsSurface() )
			{
				for ( int j = 0; j < _nbLightSamples; j++ )
				{
					lightSample = p_scene.getLights().at( i )->sample( hitRecord._point );
					Ray shadowRay( hitRecord._point, lightSample._direction );
					shadowRay.offset( hitRecord._normal );

					cosTheta = glm::max( 0.f, glm::dot( lightSample._direction, hitRecord._normal ) );

					_fr = hitRecord._object->getMaterial()->shade( p_ray, hitRecord, lightSample );
					color += hitRecord._object->getMaterial()->getFlatColor() * lightSample._radiance * cosTheta * _fr;

					if ( !p_scene.intersectAny( shadowRay, SHADOW_EPSILON, lightSample._distance ) )
					{
						color += hitRecord._object->getMaterial()->getFlatColor() * lightSample._radiance * cosTheta
								 * _fr;
					}
				}
				color /= _nbLightSamples;
			}
			else
			{
				if ( !p_scene.intersectAny( shadowRay, SHADOW_EPSILON, lightSample._distance ) )
				{
					color += hitRecord._object->getMaterial()->getFlatColor() * lightSample._radiance * cosTheta * _fr;
				}
			}
		}
		return color;
	}

	Vec3f WhittedIntegrator::trace( const Scene & p_scene, const Ray & p_ray, const float p_tMin, const float p_tMax, int p_nbounces, bool isInside ) const
	{
		//isInside = si le rayon est dedans ou dehors comme ça n1 et n2 sont inversé ou pas
		HitRecord hitRecord;

		if (p_scene.intersect(p_ray, p_tMin, p_tMax, hitRecord)) {

			if ( p_nbounces == 0 ) { return _directLighting( p_scene, p_ray, hitRecord, p_tMax ); }

			if ( hitRecord._object->getMaterial()->isMirror() )
			{
				Ray reflectRay = Ray( hitRecord._point, glm::reflect( p_ray.getDirection(), hitRecord._normal ) );
				reflectRay.offset( hitRecord._normal );
				return trace( p_scene, reflectRay, p_tMin, p_tMax, p_nbounces - 1, isInside);
			}

			else if (hitRecord._object->getMaterial()->isTransparent()) 
			{ 
				float n1 = 1.f, n2 = hitRecord._object->getMaterial()->getIOR();
				if ( isInside )
				{
					n1 = hitRecord._object->getMaterial()->getIOR();
					n2 = 1.f;
				}
				Ray	  reflectRay = Ray( hitRecord._point, glm::normalize(glm::reflect( p_ray.getDirection(), hitRecord._normal )) );
				reflectRay.offset( hitRecord._normal );

				Vec3f reflectLi = trace( p_scene, reflectRay, 0, p_tMax, p_nbounces - 1, isInside);
				float kr		= 1.f;
				float coeff		= n1 / n2;

				float cosTheta_i = glm::dot( p_ray.getDirection(), hitRecord._normal );
				float sinTheta_i = glm::sqrt( 1.f - pow( cosTheta_i, 2 ) );
				float cosTheta_t = glm::sqrt( 1.f - pow( coeff * sinTheta_i, 2 ) );

				float rs = pow( ( n1 * cosTheta_i - n2 * cosTheta_t ) / ( n1 * cosTheta_i + n2 * cosTheta_t ), 2 );
				float rp = pow( ( n1 * cosTheta_t - n2 * cosTheta_i ) / ( n1 * cosTheta_t + n2 * cosTheta_i ), 2 );

				kr = ( rs + rp ) * 0.5f;
				if ( kr < 1.f )
				{
					Vec3f refractRay = glm::refract( p_ray.getDirection(), hitRecord._normal, coeff );

					Ray ray_refraction = Ray( hitRecord._point, refractRay );
					ray_refraction.offset( -hitRecord._normal );
					Vec3f refractLi = trace( p_scene, ray_refraction, p_tMin, p_tMax, p_nbounces - 1, !isInside );

					return kr * reflectLi + ( 1.f - kr ) * refractLi;
					std::cout << "here" << std::endl;
				}
				else { 
					return reflectLi; }
			}

			else { return _directLighting( p_scene, p_ray, hitRecord, p_tMax );
			}
		}

		return _backgroundColor;
	}

} // namespace RT_ISICG