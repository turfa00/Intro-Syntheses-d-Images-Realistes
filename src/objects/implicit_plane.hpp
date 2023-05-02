#ifndef __IMPLICIT_PLANE__
#define __IMPLICIT_PLANE__

#include "base_object.hpp"
#include "implicit_surface.hpp"

namespace RT_ISICG
{
	class ImplicitPlane : public ImplicitSurface
	{
	  public:
		ImplicitPlane()			   = delete;
		virtual ~ImplicitPlane() = default;

		ImplicitPlane( const std::string & p_name, const Vec3f & p_center, const Vec3f & p_normal )
			: ImplicitSurface( p_name ), _center( p_center ), _normal( glm::normalize(p_normal) )
		{
		}

	  private:
		// Signed Distance Function
		float _sdf( const Vec3f & p_point ) const { 
			float disp = 15.f;
			float p1 = glm::dot( p_point, _normal ) + 1.f;
			float p2   = sin( disp * p_point.x ) * sin( disp * p_point.y ) * sin( disp * p_point.z );
			return p1 + p2;
			//return glm::dot( p_point, _normal ) + 1.f;
		}

	  private:
		const float _minDistance = 1e-4f;
		Vec3f		_center, _normal;
	};
} // namespace RT_ISICG

#endif