#ifndef __RT_ISICG_IMPLICIT_SURFACE__
#define __RT_ISICG_IMPLICIT_SURFACE__

#include "base_object.hpp"

namespace RT_ISICG
{
	class ImplicitSurface : public BaseObject
	{
	  public:
		ImplicitSurface()		   = delete;
		virtual ~ImplicitSurface() = default;

		ImplicitSurface( const std::string & p_name ) : BaseObject( p_name ) {}

		// Check for nearest intersection between p_tMin and p_tMax : if found fill p_hitRecord.
		virtual bool intersect( const Ray & p_ray,
								const float p_tMin,
								const float p_tMax,
								HitRecord & p_hitRecord ) const override;

		// Check for any intersection between p_tMin and p_tMax.
		virtual bool intersectAny( const Ray & p_ray, const float p_tMin, const float p_tMax ) const override;

	  private:
		// Signed Distance Function
		virtual float _sdf( const Vec3f & p_point ) const = 0;

		// Evaluate normal by computing gradient at 'p_point'
		virtual Vec3f _evaluateNormal( const Vec3f & p_point ) const
		{
			float fx = _sdf( Vec3f( p_point.x + _minDistance, p_point.y, p_point.z ) )
					   - _sdf( Vec3f( p_point.x - _minDistance, p_point.y, p_point.z ) );
			float fy = _sdf( Vec3f( p_point.x, p_point.y + _minDistance, p_point.z ) )
					   - _sdf( Vec3f( p_point.x, p_point.y - _minDistance, p_point.z ) );
			float fz = _sdf( Vec3f( p_point.x, p_point.y, p_point.z + _minDistance ) )
					   - _sdf( Vec3f( p_point.x, p_point.y, p_point.z - _minDistance ) );
			return glm::normalize(Vec3f(fx, fy, fz));
		}

	  private:
		const float _minDistance = 1e-4f;
	};

} // namespace RT_ISICG

#endif // __RT_ISICG_IMPLICIT_SURFACE__
