#ifndef __RT_ISICG_WHITTED_INTEGRATOR__
#define __RT_ISICG_WHITTED_INTEGRATOR__

#include "base_integrator.hpp"
#include "materials/lambert_material.hpp"

namespace RT_ISICG
{
	class WhittedIntegrator : public BaseIntegrator
	{
	  public:
		WhittedIntegrator() : BaseIntegrator() {}
		virtual ~WhittedIntegrator() = default;

		const IntegratorType getType() const override { return IntegratorType::RAY_CAST; }

		// Return incoming luminance.
		Vec3f Li( const Scene & p_scene, const Ray & p_ray, const float p_tMin, const float p_tMax ) const override;

		Vec3f trace( const Scene & p_scene, const Ray & p_ray, const float p_tMin, const float p_tMax, int p_nbounces ) const;

	  private:
		Vec3f _directLighting( const Scene & p_scene, const Ray & p_ray, const float p_tMin, const float p_tMax ) const;
		int	  _nbLightSamples = 2;
		int	  _nbBounce		  = 5;
	};

} // namespace RT_ISICG

#endif // __RT_ISICG_WHITTED_INTEGRATOR__
