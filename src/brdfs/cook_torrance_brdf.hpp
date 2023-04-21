#ifndef __RT_ISICG_COOK_TORRANCE_BRDF__
#define __RT_ISICG_COOK_TORRANCE_BRDF__

#include "defines.hpp"
#include <hit_record.hpp>
#include <lights/light_sample.hpp>

namespace RT_ISICG
{
	class CookTorranceBRDF
	{
	  public:
		CookTorranceBRDF( const Vec3f & p_ks ) : _ks( p_ks ) {};

		inline Vec3f evaluate( HitRecord hitRecord, LightSample lightSample, Vec3f observation ) const
		{
			_incidence			  = lightSample._direction;
			float theta_incidence = _incidence.y / _incidence.x;
			_observation		  = observation;
			_reflet				  = glm::reflect( _incidence, hitRecord._normal );

			angleObservation = glm::dot( observation, hitRecord._normal );
			angleIncidence	 = glm::dot( hitRecord._normal, _incidence );
			alpha				  = glm::pow(s, 2 );
			
			n = hitRecord._normal;
			h		= ( angleIncidence + angleObservation ) / glm::length( angleIncidence + angleObservation );
			float a = n * h;
			D = ( alpha * alpha ) / glm::pow((INV_PIf * ((n*h)*(n*h) * (glm::pow(alpha, 2) - 1.f) + 1.f)), 2);

			//G =
			
			float p = h * _observation;
			F = Fo + ( 1 - Fo ) * ( 1 - glm::pow(p, 2 ) );
			 
			// theta		 = glm::acos(glm::dot( _incidence, hitRecord._normal ));
			//return _ks / glm::cos( theta ) * glm::cos( glm::pow( alpha, s ) );

			return ( D * F * G / ( 4 * _observation * n * _incidence * n ) );
		}

		inline const Vec3f & getKs() const { return _ks; }

	  private:
		mutable float F = 0.f, G = 0.f;
		mutable Vec3f D	  = VEC3F_ZERO;
		mutable Vec3f _ks = WHITE, _incidence = VEC3F_ZERO, _observation = VEC3F_ZERO, _reflet = VEC3F_ZERO, n = VEC3F_ZERO;
		mutable float alpha = 0.f, s = 0.3f, Fo = 0.f, h = 0.f, angleObservation = 0.f, angleIncidence = 0.f; //s = rugosite
	};
} // namespace RT_ISICG

#endif // __RT_ISICG_COOK_TORRANCE_BRDF__
