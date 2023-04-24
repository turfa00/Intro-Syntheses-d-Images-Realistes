#ifndef __RT_ISICG_COOK_TORRANCE_MATERIAL__
#define __RT_ISICG_COOK_TORRANCE_MATERIAL__

#include "base_material.hpp"
#include "brdfs/oren_nayar_brdf.hpp"
#include "brdfs/cook_torrance_brdf.hpp"

namespace RT_ISICG
{
	class CookTorranceMaterial : public BaseMaterial
	{
	  public:
		CookTorranceMaterial( const std::string & p_name, const Vec3f & p_diffuse )
			: BaseMaterial( p_name ), _lambBrdf( p_diffuse ), _orenbBrdf( p_diffuse ),
			  _cookBrdf( Vec3f( 1.f, 0.85f, 0.57f ) )
		{
		}

		virtual ~CookTorranceMaterial() = default;

		Vec3f shade( const Ray &		 p_ray,
					 const HitRecord &	 p_hitRecord,
					 const LightSample & p_lightSample ) const override
		{
			return (1 - _metalness) * _lambBrdf.evaluate() + _metalness * _cookBrdf.evaluate(p_hitRecord, p_lightSample, p_ray);
		}

		inline const Vec3f & getFlatColor() const override { return _orenbBrdf.getKd(); }

	  protected:
		LambertBRDF	 _lambBrdf;
		OrenNayarBRDF _orenbBrdf;
		CookTorranceBRDF _cookBrdf;
		float		  _metalness = 0.5f;
	};

} // namespace RT_ISICG

#endif // __RT_ISICG_MATTE_MATERIAL__
