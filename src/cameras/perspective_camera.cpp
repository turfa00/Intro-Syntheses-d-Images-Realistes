#include "perspective_camera.hpp"
#include <glm/gtx/string_cast.hpp>

namespace RT_ISICG
{
	PerspectiveCamera::PerspectiveCamera( const float p_aspectRatio ) : _aspectRatio( p_aspectRatio )
	{
		_updateViewport();
	}

	PerspectiveCamera::PerspectiveCamera( const Vec3f & p_position,
										  const Vec3f & p_lookAt,
										  const Vec3f & p_up,
										  const float	p_fovy,
										  const float	p_aspectRatio )
		: BaseCamera( p_position ), _fovy( p_fovy ), _aspectRatio( p_aspectRatio )
	{
		/// TODO ! _u ? _v ? _w ?

		_updateViewport();
	}

	void PerspectiveCamera::_updateViewport()
	{
		_viewportHeight  = _focalDistance * glm::tan( _fovy / 2 );
		_viewportWidth   = _aspectRatio * _viewportHeight;

		_viewportTopLeftCorner = _position + Vec3f( 0.f, 0.f, _focalDistance ) + Vec3f( 0.f, _viewportHeight / 2, 0.f )
								 - Vec3f( _viewportWidth / 2, 0.f, 0.f );
		Vec3f _viewportBottomLeftCorner = _position + Vec3f( 0.f, 0.f, _focalDistance )
										  - Vec3f( 0.f, _viewportHeight / 2, 0.f ) - Vec3f( _viewportWidth / 2, 0.f, 0.f );
		Vec3f _viewportBottomRightCorner = _position + Vec3f( 0.f, 0.f, _focalDistance )
									   - Vec3f( 0.f, _viewportHeight / 2, 0.f ) + Vec3f( _viewportWidth / 2, 0.f, 0.f );
		_viewportV = _viewportBottomLeftCorner - _viewportTopLeftCorner;
		_viewportU = _viewportBottomLeftCorner - _viewportBottomRightCorner;
		/// TODO ! _viewportTopLeftCorner ?	_viewportU ? _viewportV ?
	}

} // namespace RT_ISICG
