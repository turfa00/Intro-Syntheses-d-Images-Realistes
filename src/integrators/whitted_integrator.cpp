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
				//Reflection
				Ray reflectionRay = Ray( hitRecord._point, glm::normalize( glm::reflect( p_ray.getDirection(), hitRecord._normal ) ) );
				reflectionRay.offset( hitRecord._normal );
				Vec3f reflectionColor = trace( p_scene, reflectionRay, 0, p_tMax, p_nbounces - 1, isInside );

				float n1 = 1.f, n2 = hitRecord._object->getMaterial()->getIOR();
				if ( isInside )
				{
					std::swap( n1, n2 );
				}
				float eta = n1 / n2;
				//Refraction
				Vec3f refractRay	= glm::refract( p_ray.getDirection(), hitRecord._normal, eta );
				Ray refractionRay = Ray( hitRecord._point, refractRay );
				Vec3f refractionColor = trace( p_scene, refractionRay, 0, p_tMax, p_nbounces - 1, !isInside );

				//Fresnel
				float kr, kt;
				float cosi = glm::clamp( -1.f, 1.f, glm::dot( p_ray.getDirection(), hitRecord._normal ) );
				//float etai = 1, etat = hitRecord._object->getMaterial()->getIOR();
				float etai = n1, etat = n2;
				if ( cosi > 0 ) { std::swap( etai, etat ); }
				// Compute sini using Snell's law
				float sint = etai / etat * sqrtf( std::max( 0.f, 1 - cosi * cosi ) );
				// Total internal reflection
				if ( sint >= 1 ) { kr = 1; }
				else
				{
					float cost = sqrtf( std::max( 0.f, 1 - sint * sint ) );
					cosi	   = fabsf( cosi );
					float Rs   = ( ( etat * cosi ) - ( etai * cost ) ) / ( ( etat * cosi ) + ( etai * cost ) );
					float Rp   = ( ( etai * cosi ) - ( etat * cost ) ) / ( ( etai * cosi ) + ( etat * cost ) );
					kr		   = ( Rs * Rs + Rp * Rp ) / 2;
				}

				return kr * reflectionColor + ( ( 1.f - kr ) * refractionColor );
				//https://www.scratchapixel.com/lessons/3d-basic-rendering/introduction-to-ray-tracing/ray-tracing-practical-example.html
			}

			else { return _directLighting( p_scene, p_ray, hitRecord, p_tMax );
			}
		}

		return _backgroundColor;
	}

} // namespace RT_ISICG