#ifndef __RT_ISICG_PLANE_GEOMETRY__
#define __RT_ISICG_PLANE_GEOMETRY__

#include "base_geometry.hpp"

namespace RT_ISICG
{
	class PlaneGeometry : public BaseGeometry
	{
	  public:
		PlaneGeometry() = delete;
		virtual ~PlaneGeometry() = default;

		PlaneGeometry( const Vec3f & p_point, const Vec3f p_normal ) : point( p_point ), normal( p_normal ) {}

		inline const Vec3f & getPoint() const { return point; }
		inline const Vec3f	 getNormal() const { return normal; }

		bool intersect( const Ray & p_ray, float & p_t1, float & p_t2 ) const;

	  private:
		Vec3f point = VEC3F_ZERO;
		Vec3f normal = VEC3F_ZERO;
	};

} // namespace RT_ISICG

#endif // __RT_ISICG_PLANE_GEOMETRY__
