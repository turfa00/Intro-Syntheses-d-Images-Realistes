#ifndef __RT_ISICG_COOK_TORRANCE_MATERIAL__
#define __RT_ISICG_COOK_TORRANCE_MATERIAL__

#include "base_material.hpp"
#include "brdfs/oren_nayar_brdf.hpp"

namespace RT_ISICG
{
	class CookTorranceMaterial : public BaseMaterial
	{
	  public:
		CookTorranceMaterial( const std::string & p_name, const Vec3f & p_diffuse )
			: BaseMaterial( p_name ), _brdf( p_diffuse )
		{
		}

		virtual ~CookTorranceMaterial() = default;

		Vec3f shade( const Ray &		 p_ray,
					 const HitRecord &	 p_hitRecord,
					 const LightSample & p_lightSample ) const override
		{
			return _brdf.evaluate( p_hitRecord, p_lightSample, p_ray.getOrigin() );
		}

		inline const Vec3f & getFlatColor() const override { return _brdf.getKd(); }

	  protected:
		OrenNayarBRDF _brdf;
		float		  _metalness = 0.f;
	};

} // namespace RT_ISICG

#endif // __RT_ISICG_MATTE_MATERIAL__
