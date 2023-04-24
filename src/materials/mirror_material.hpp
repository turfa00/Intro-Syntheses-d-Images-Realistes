#ifndef __RT_ISICG_MIRROR_MATERIAL__
#define __RT_ISICG_MIRROR_MATERIAL__

#include "base_material.hpp"
#include "defines.hpp"

namespace RT_ISICG
{
	class MirrorMaterial : public BaseMaterial
	{
	  public:
		MirrorMaterial( const std::string & p_name, const Vec3f & p_color ) : BaseMaterial( p_name ), _color( p_color )
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
		Vec3f _color = Vec3f( 1.f, 1.f, 1.f );
	};

} // namespace RT_ISICG

#endif // __RT_ISICG_MIRROR_MATERIAL__
