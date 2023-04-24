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
		CookTorranceBRDF( const Vec3f & p_Fo, const float p_rugosite ) : Fo( p_Fo ), s(p_rugosite) {};

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
			//Vec3f h = ( p_wo + p_wi ) / glm::length( p_wo + p_wi );
			h		= ( _incidence + _observation ) / glm::length( _incidence + _observation );
			float a = glm::dot(n, h);
			//Compute D
			D = ( alpha * alpha ) / ((PIf * glm::pow(glm::dot(n,h), 2) * (glm::pow(alpha, 2) - 1.f) + 1.f));

			//Compute G1
			G1 = x / ( x * ( 1.f - k ) + k );

			// Compute G
			float k = ( s + 1.f ) * ( s + 1.f ) / 8.f;
			G		= ( glm::dot( n, wo ) / ( glm::dot( n, wo ) * ( 1.f - k ) + k ) )
				* ( ( glm::dot( n, wi ) / ( glm::dot( n, wi ) * ( 1.f - k ) + k ) ) );
			
			float x = pow( ( 1.f - glm::dot( h, wo ) ), 5 );
			F		= Fo + ( 1.f - Fo ) * x;

			return ( D * F * G / ( 4 * glm::dot(wo, n) * glm::dot(wi, n)) );
		}

		//inline const Vec3f & getKs() const { return _ks; }

	  private:
		mutable float G1 = 0.f, G = 0.f, D = 0.f;
		mutable float x = 0.f, k = 0.f;
		mutable Vec3f _ks = WHITE, _incidence = VEC3F_ZERO, _observation = VEC3F_ZERO, _reflet = VEC3F_ZERO, n = VEC3F_ZERO, h = VEC3F_ZERO;
		mutable Vec3f		  wo = VEC3F_ZERO, wi = VEC3F_ZERO, Fo = VEC3F_ZERO, F = VEC3F_ZERO;
		mutable float alpha = 0.f, s = 0.3f, angleObservation = 0.f, angleIncidence = 0.f; //s = rugosite
	};
} // namespace RT_ISICG

#endif // __RT_ISICG_COOK_TORRANCE_BRDF__
