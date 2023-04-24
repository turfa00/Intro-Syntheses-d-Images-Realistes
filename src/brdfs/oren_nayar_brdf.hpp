#ifndef __RT_ISICG_OREN_NAYAR_BRDF__
#define __RT_ISICG_OREN_NAYAR_BRDF__

#include "defines.hpp"

namespace RT_ISICG
{
	class OrenNayarBRDF
	{
	  public:
		OrenNayarBRDF( const Vec3f & p_kd , const float p_sigma) : _kd( p_kd ), sigma(p_sigma)
		{ 
		};

		// * INV_PIf : could be done in the constructor...
		inline Vec3f evaluate( HitRecord hitRecord, LightSample lightSample, Vec3f observation ) const
		{ 
			this->_incidence   = lightSample._direction;
			this->_observation = -observation;

			theta_incidence	  = _incidence.y / _incidence.x;
			theta_observation = _observation.y / _observation.x;

			phi_incidence	= glm::acos( _incidence.z / glm::length( _incidence ) );
			phi_observation = glm::acos( _observation.z / glm::length( _observation ) );

			A	  = 1.f - ( ( 0.5f * sigma * sigma ) / ( ( sigma * sigma ) + 0.33f ) );
			B	  = 0.45f * ( sigma * sigma / ( ( sigma * sigma ) + 0.09f ) );
			alpha = glm::max( theta_incidence, theta_observation );
			beta  = glm::min( theta_incidence, theta_observation );
			return _kd * INV_PIf * ( A + ( B * glm::max( 0.f, glm::cos( phi_incidence - phi_observation ) ) ) * glm::sin( alpha ) * glm::tan( beta ) ); 
		}

		inline const Vec3f & getKd() const { return _kd; }

	  private:
		mutable Vec3f  _kd = WHITE, _incidence = VEC3F_ZERO, _observation = VEC3F_ZERO;
		mutable float  A = 0.f, B = 0.f, alpha = 0.f, beta = 0.f, sigma = 0.4f;
		mutable float   theta_incidence = 0.f, theta_observation = 0.f, phi_incidence = 0.f, phi_observation = 0.f;
	};
} // namespace RT_ISICG

#endif // __RT_ISICG_OREN_NAYAR_BRDF___
