#ifndef __IMPLICIT_BOX__
#define __IMPLICIT_BOX__

#include "base_object.hpp"
#include "implicit_surface.hpp"

namespace RT_ISICG
{
	class ImplicitBox : public ImplicitSurface
	{
	  public:
		ImplicitBox()			   = delete;
		virtual ~ImplicitBox() = default;

		ImplicitBox( const std::string & p_name, const Vec3f & p_center, const float p_height )
			: ImplicitSurface( p_name ), _center( p_center ), _height( p_height )
		{
		}

	  private:
		// Signed Distance Function
		float _sdf( const Vec3f & p_point ) const 
		{
			Vec2f q = _height * Vec2f( _center.x, -_center.y ) / _center.y;
			Vec2f mm = Vec2f( p_point.x, p_point.z );
			Vec2f w = Vec2f( glm::length( mm ), p_point.y );

			Vec2f  a = w - q * glm::clamp( dot( w, q ) / dot( q, q ), 0.f, 1.f );
			Vec2f  b = w - q * Vec2f( glm::clamp( w.x / q.x, 0.f, 1.f ), 1.f );
			float k = glm::sign( q.y );
			float d = glm::min( dot( a, a ), dot( b, b ) );
			float s = glm::max( k * ( w.x * q.y - w.y * q.x ), k * ( w.y - q.y ) );
			return glm::sqrt( d ) * glm::sign( s ) + 0.2f;
		}

	  private:
		const float _minDistance = 1e-4f;
		Vec3f		_center;
		float		_height;
		mutable Vec3f point;
	};
} // namespace RT_ISICG

#endif