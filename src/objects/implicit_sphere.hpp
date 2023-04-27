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

	  private:
		// Signed Distance Function
		float _sdf( const Vec3f & p_point ) const { return glm::distance( p_point, _center ) - _radius; }

	  private:
		const float _minDistance = 1e-4f;
		Vec3f _center;
		float		_radius;
	};
}

#endif