#ifndef __RT_ISICG_OREN_NAYAR_BRDF__
#define __RT_ISICG_OREN_NAYAR_BRDF__

#include "defines.hpp"

namespace RT_ISICG
{
	class OrenNayarBRDF
	{
	  public:
		OrenNayarBRDF( const Vec3f & p_kd , const float pente, const float incidence, const float observation) : _kd( p_kd ) 
		{ 
			gamma = pente;
			this->incidence = incidence;
			this->observation = observation;
			A	  = 1 - ( 0.5f ) * ( gamma * gamma / (( gamma * gamma ) + 0.09 ));
			B	  = 0.45 * ( gamma * gamma / ( ( gamma * gamma ) + 0.09 ) );
			alpha = glm::max(incidence, observation);
			beta  = glm::min(incidence, observation);
		};

		// * INV_PIf : could be done in the constructor...
		inline Vec3f evaluate() const { 
				
			return _kd * INV_PIf * ( A + ( B * glm::max() * glm::sin( alpha ) * glm::tan(beta) ) ); 
		}

		inline const Vec3f & getKd() const { return _kd; }

	  private:
		Vec3f _kd = WHITE;
		double A, B, alpha, beta, gamma;
		float  incidence, observation;
	};
} // namespace RT_ISICG

#endif // __RT_ISICG_OREN_NAYAR_BRDF___
