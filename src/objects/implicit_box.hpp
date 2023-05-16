#ifndef __IMPLICIT_BOX__
#define __IMPLICIT_BOX__

#include "base_object.hpp"
#include "implicit_surface.hpp"
#include "Windowsnumerics.h"
namespace RT_ISICG
{
	class ImplicitBox : public ImplicitSurface
	{
	  public:
		ImplicitBox()			   = delete;
		virtual ~ImplicitBox() = default;

		ImplicitBox( const std::string & p_name, const Vec3f & p_size, const Vec3f & p_center ) : ImplicitSurface( p_name ), _size( p_size ), _center(p_center)
		{
		}
		float _sdf( const Vec3f & p_point ) const
		{
			Vec3f q = abs( p_point - _center ) - _size;
			// return glm::length( glm::max( q, 0.f ) ) + glm::min( glm::max( q.x, glm::max( q.y, q.z ) ), 0.f );
			return glm::length( glm::max( q, 0.f ) ) + glm::min( glm::max( q.x, glm::max( q.y, q.z ) ), 0.f );

			// http://www.cs.cornell.edu/courses/cs6630/2012sp/slides/Boyadzhiev-Matzen-InstantRadiosity.pdf //Instant
			// radiosity
		}
	  private:
		// Signed Distance Function
		

	  private:
		const float _minDistance = 1e-4f;
		Vec3f		  _size, _center = Vec3f(0.f);
		float		_height;
		mutable Vec3f point;
	};
} // namespace RT_ISICG

#endif