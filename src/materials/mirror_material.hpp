#ifndef __RT_ISICG_MIRROR_MATERIAL__
#define __RT_ISICG_MIRROR_MATERIAL__

#include "base_material.hpp"
#include "defines.hpp"

namespace RT_ISICG
{
	class MirrorMaterial : public BaseMaterial
	{
	  public:
		MirrorMaterial( const std::string & p_name ) : BaseMaterial( p_name )
		{
		}

		virtual ~MirrorMaterial() = default;

		Vec3f shade( const Ray & p_ray, const HitRecord & p_hit, const LightSample & p_lightSample ) const // override
		{
			return VEC3F_ZERO;
		}

		inline const Vec3f & getFlatColor() const override { return VEC3F_ZERO; }

		bool isMirror() const override { return true;
		}

	  protected:
		Vec3f _color = BLACK;
	};

} // namespace RT_ISICG

#endif // __RT_ISICG_MIRROR_MATERIAL__
