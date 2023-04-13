#ifndef __RT_ISICG_PLASTIC_MATERIAL__
#define __RT_ISICG_PLASTIC_MATERIAL__

#include "base_material.hpp"
#include "brdfs/oren_nayar_brdf.hpp"
#include "brdfs/phong_brdf.hpp"

namespace RT_ISICG
{
	class PlasticMaterial : public BaseMaterial
	{
	  public:
		PlasticMaterial( const std::string & p_name,
					   const Vec3f &	   p_diffuse,
					   const Vec3f &       p_specular )
			: BaseMaterial( p_name ), _lambertBrdf( p_diffuse ), _phongBrdf( p_specular )
		{
		}

		virtual ~PlasticMaterial() = default;

		Vec3f shade( const Ray &		 p_ray,
					 const HitRecord &	 p_hitRecord,
					 const LightSample & p_lightSample ) const override
		{
			//return _phongBrdf.evaluate( p_hitRecord, p_lightSample, p_ray.getOrigin() );
			return _lambertBrdf.evaluate( )
				   + _phongBrdf.evaluate( p_hitRecord, p_lightSample, p_ray.getOrigin() );
		}

		inline const Vec3f & getFlatColor() const override { return _lambertBrdf.getKd(); }

	  protected:
		LambertBRDF	  _lambertBrdf;
		PhongBRDF	  _phongBrdf;
	};

} // namespace RT_ISICG

#endif // __RT_ISICG_PLASTIC_MATERIAL__
