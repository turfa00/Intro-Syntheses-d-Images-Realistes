#ifndef __RT_ISICG_WHITTED_INTEGRATOR__
#define __RT_ISICG_WHITTED_INTEGRATOR__

#include "base_integrator.hpp"
#include "materials/lambert_material.hpp"

namespace RT_ISICG
{
	class RadiosityIntegrator : public BaseIntegrator
	{
	  public:
		RadiosityIntegrator() : BaseIntegrator() {}
		virtual ~RadiosityIntegrator() = default;

		const IntegratorType getType() const override { return IntegratorType::RADIOSITY; }

		// Return incoming luminance.
		Vec3f Li( const Scene & p_scene, const Ray & p_ray, const float p_tMin, const float p_tMax ) const override;

		Vec3f trace( const Scene & p_scene,
					 const Ray &   p_ray,
					 const float   p_tMin,
					 const float   p_tMax,
					 int		   p_nbounces,
					 bool		   isInside ) const;

		Vec3f _directLighting( const Scene &	 p_scene,
							   const Ray &		 p_ray,
							   const HitRecord & hitRecord,
							   const float		 p_tMax ) const;

	  private:
		//mutable LightList _lightList;
		//int				  _radiosityLightSamples = 2;
		int _nbLightSamples = 12;
		int _nbBounce		= 6;
	};

} // namespace RT_ISICG

#endif // __RT_ISICG_WHITTED_INTEGRATOR__
