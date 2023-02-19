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
		//_u = glm::cross( p_lookAt, p_up );
		//_v = glm::normalize(p_up);
		//_v = glm::cross(_u, );
		_w = - glm::normalize(p_lookAt - p_position);
		_u = glm::normalize(glm::cross(p_up, _w));
		//_u = glm::normalize(glm::cross(_w, p_up));
		_v = glm::normalize( glm::cross(_u, _w));
		_updateViewport();
	}

	void PerspectiveCamera::_updateViewport()
	{
		_viewportHeight  = 2.0f * _focalDistance * glm::tan( glm::radians(_fovy / 2.0f ));
		_viewportWidth   = _aspectRatio * _viewportHeight;

		_viewportV			   = _v * _viewportHeight;
		_viewportU			   = _u * _viewportWidth;

		_viewportTopLeftCorner = _position - ( _w * _focalDistance ) + ( _viewportV * 0.5f ) - ( _viewportU * 0.5f );

		/// TODO ! _viewportTopLeftCorner ?	_viewportU ? _viewportV ?
	}

} // namespace RT_ISICG
