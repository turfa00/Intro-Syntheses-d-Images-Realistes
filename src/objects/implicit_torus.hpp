#ifndef __IMPLICIT_TORUS__
#define __IMPLICIT_TORUS__

#include "Windowsnumerics.h"
#include "base_object.hpp"
#include "implicit_surface.hpp"
namespace RT_ISICG
{
	class ImplicitTorus : public ImplicitSurface
	{
	  public:
		ImplicitTorus()			  = delete;
		virtual ~ImplicitTorus() = default;

		ImplicitTorus( const std::string & p_name, const Vec3f & p_center, const float p_height, const float p_ra, const float p_rb)
			: ImplicitSurface( p_name ), _height(p_height), _center( p_center ), ra( p_ra ), rb( p_rb )
		{
		}
		// Signed Distance Function
		float _sdf( const Vec3f & p_point ) const
		{
			float thickness = 0.1f;
			Vec2f t			= Vec2f( 2.f, 1.f );
			Vec2f p			= Vec2f( p_point.x - _center.x, p_point.z - _center.z );
			Vec2f q			= Vec2f( glm::length( p ) - t.x, p_point.y - _center.y );
			float point		= glm::length( q ) - t.y;
			return glm::abs( point ) - thickness;

			/* Vec2f d = Vec2f( glm::length( p ) - 2.0 * ra + rb, glm::abs( p_point.y - _center.y ) - _height );
			//return glm::min( glm::max( d.x, d.y ), 0.f ) + glm::length( glm::max( d, 0.f ) ) - rb;
			float point = glm::min( glm::max( d.x, d.y ), 0.f ) + glm::length( glm::max( d, 0.f ) ) - rb;
			return glm::abs( point ) - thickness;*/
		}
	  private:
		

	  private:
		const float	  _minDistance = 1e-4f;
		Vec3f		  _size, _center = Vec3f( 0.f );
		float		  _height, ra, rb;
		mutable Vec3f point;
	};
} // namespace RT_ISICG

#endif