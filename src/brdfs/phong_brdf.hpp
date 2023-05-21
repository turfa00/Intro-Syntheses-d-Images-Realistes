#ifndef __RT_ISICG_BRDF_PHONG__
#define __RT_ISICG_BRDF_PHONG__

#include "defines.hpp"
#include <hit_record.hpp>

namespace RT_ISICG
{
	class PhongBRDF
	{
	  public:
		PhongBRDF( const Vec3f & p_ks ) : _ks( p_ks ) 
		{
		};

		inline Vec3f evaluate( HitRecord hitRecord, LightSample lightSample, Vec3f observation ) const
		{ 
			_incidence	 = lightSample._direction;
			float theta_incidence = _incidence.y / _incidence.x;
			_observation = observation;
			_reflet		 = glm::reflect( _incidence, hitRecord._normal );
			alpha		 = glm::dot( _observation, _reflet );
			theta		 = glm::dot( _incidence, hitRecord._normal );
			return _ks / glm::cos( theta ) * glm::cos( glm::pow( alpha, s ) ); 
		}

		inline const Vec3f & getKs() const { return _ks; }

	  private:
		mutable Vec3f _ks = WHITE, _incidence = VEC3F_ZERO, _observation = VEC3F_ZERO, _reflet = VEC3F_ZERO;
		mutable float alpha = 0.f, theta = 0.f, s = 8.f;
	};
} // namespace RT_ISICG

#endif // __RT_ISICG_BRDF_PHONG__
