#ifndef __RT_ISICG_OREN_NAYAR_BRDF__
#define __RT_ISICG_OREN_NAYAR_BRDF__

#include "defines.hpp"

namespace RT_ISICG
{
	class OrenNayarBRDF
	{
	  public:
		OrenNayarBRDF( const Vec3f & p_kd, const Vec3f incidence, const Vec3f observation )
			: _kd( p_kd ) // Take care of this
		{ 
			this->_incidence = incidence;
			this->_observation = observation;

			theta_incidence	  = _incidence.y / _incidence.x;
			theta_observation = _observation.y / _observation.x;

			phi_incidence	  = glm::acos(_incidence.z / glm::length(_incidence));
			phi_observation	  = glm::acos( _observation.z / glm::length( _observation ) );
			A	  = 1 - ( 0.5f ) * ( gamma * gamma / (( gamma * gamma ) + 0.09f ));
			B	  = 0.45f * ( gamma * gamma / ( ( gamma * gamma ) + 0.09f ) );
			alpha			  = glm::max( theta_incidence, theta_observation );
			beta			  = glm::min( theta_incidence, theta_observation );
		};

		// * INV_PIf : could be done in the constructor...
		inline Vec3f evaluate() const { 
			return _kd * INV_PIf * ( A + ( B * glm::max( 0.f, glm::cos( phi_incidence - phi_observation ) ) * glm::sin( alpha ) * glm::tan( beta ) ) ); 
		}

		inline const Vec3f & getKd() const { return _kd; }

	  private:
		Vec3f  _kd = WHITE, _incidence, _observation;
		float A, B, alpha, beta, gamma = 0.2f;
		float  theta_incidence = 0.f, theta_observation = 0.f, phi_incidence = 0.f, phi_observation = 0.f;
		//double  incidence, observation;
	};
} // namespace RT_ISICG

#endif // __RT_ISICG_OREN_NAYAR_BRDF___
