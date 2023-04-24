#ifndef __RT_ISICG_TRANSPARENT_MATERIAL__
#define __RT_ISICG_TRANSPARENT_MATERIAL__

#include "base_material.hpp"
#include "defines.hpp"

namespace RT_ISICG
{
	class TransparentMaterial : public BaseMaterial
	{
	  public:
		TransparentMaterial( const std::string & p_name, const float p_ior ) : BaseMaterial( p_name ), _ior(p_ior)
		{
		}

		virtual ~TransparentMaterial() = default;

		Vec3f shade( const Ray & p_ray, const HitRecord & p_hit, const LightSample & p_lightSample ) const
		{
			return VEC3F_ZERO;
		}

		inline const Vec3f & getFlatColor() const override { return VEC3F_ZERO; }

		bool isMirror() const override { return false;}

		bool isTransparent() const override{ return true; }

		const inline float & getIOR() const { return _ior; };

	  protected:
		Vec3f _color = BLACK;
		float _ior = 1.f;
	};

} // namespace RT_ISICG

#endif // __RT_ISICG_TRANSPARENT_MATERIAL__
