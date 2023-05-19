#ifndef __RT_ISICG_ORTHOGRAPHIC_CAMERA__
#define __RT_ISICG_ORTHOGRAPHIC_CAMERA__

#include "base_camera.hpp"
#include <stdlib.h>
#include <time.h>
namespace RT_ISICG
{
	class OrthographicCamera : public BaseCamera
	{
	  public:
		OrthographicCamera( const Vec3f & p_position,
						   const Vec3f & p_lookAt,
						   const Vec3f & p_up,
						   const float	 p_fovy,
						   const float	 p_aspectRatio );

		~OrthographicCamera() = default;

		inline Ray generateRay( const float p_sx, const float p_sy ) const override
		{
			Vec3f viewportPosition = _viewportTopLeftCorner - _viewportV * p_sy + _viewportU * p_sx;
			Vec3f rayOrigin		   = viewportPosition;
			Vec3f rayDirection	   =  -_w;
			return Ray( rayOrigin, glm::normalize( rayDirection ) );
		}

	  private:
		void _updateViewport();

	  private:

		// Local coordinates system
		Vec3f _u = Vec3f( 1.f, 0.f, 0.f );
		Vec3f _v = Vec3f( 0.f, 1.f, 0.f );
		Vec3f _w = Vec3f( 0.f, 0.f, -1.f );

		// Viewport data
		Vec3f _viewportTopLeftCorner = VEC3F_ZERO; // Top left corner position
		Vec3f _viewportU			 = VEC3F_ZERO; // Horizontal vector
		Vec3f _viewportV			 = VEC3F_ZERO; // Vertical vector

		float _viewportHeight = 0.f;
		float _viewportWidth  = 0.f;
	};
} // namespace RT_ISICG

#endif // __RT_ISICG_ORTHOGRAPHIC_CAMERA__
