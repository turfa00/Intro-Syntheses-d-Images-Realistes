#ifndef __IMPLICIT_SPHERE__
#define __IMPLICIT_SPHERE__

#include "base_object.hpp"
#include "implicit_surface.hpp"

namespace RT_ISICG
{
	class ImplicitSphere : public ImplicitSurface
	{
	  public:
		ImplicitSphere()		   = delete;
		virtual ~ImplicitSphere() = default;

		ImplicitSphere( const std::string & p_name, const Vec3f & p_center, const float p_radius ) : ImplicitSurface( p_name ), _center(p_center), _radius(p_radius) {}

		// Check for nearest intersection between p_tMin and p_tMax : if found fill p_hitRecord.
		/* bool intersect( const Ray & p_ray,
						const float p_tMin,
						const float p_tMax,
						HitRecord & p_hitRecord ) const override;*/

		// Check for any intersection between p_tMin and p_tMax.
		//bool intersectAny( const Ray & p_ray, const float p_tMin, const float p_tMax ) const override;

	  private:
		// Signed Distance Function
		float _sdf( const Vec3f & p_point ) const { return glm::distance( p_point, _center ) - _radius; }

		// Evaluate normal by computing gradient at 'p_point'
		virtual Vec3f _evaluateNormal( const Vec3f & p_point ) const
		{
			/// TODO
			return p_point - _radius;
		}

	  private:
		const float _minDistance = 1e-4f;
		Vec3f _center;
		float		_radius;
	};
}

#endif