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

		const IntegratorType getType() const override { return IntegratorType::WHITTED; }

		// Return incoming luminance.
		Vec3f Li( const Scene & p_scene, const Ray & p_ray, const float p_tMin, const float p_tMax ) const override;

		Vec3f trace( const Scene & p_scene, const Ray & p_ray, const float p_tMin, const float p_tMax, int p_nbounces, bool isInside ) const;

		Vec3f _directLighting( const Scene & p_scene, const Ray & p_ray, const HitRecord & hitRecord, const float p_tMax ) const;

	  private:
		int	  _nbLightSamples = 6;
		int	  _nbBounce		  = 6;
	};

} // namespace RT_ISICG

#endif // __RT_ISICG_WHITTED_INTEGRATOR__
