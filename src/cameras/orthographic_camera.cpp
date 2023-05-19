#include "orthographic_camera.hpp"
#include <glm/gtx/string_cast.hpp>

namespace RT_ISICG
{
	
	OrthographicCamera::OrthographicCamera( const Vec3f & p_position,
										  const Vec3f & p_lookAt,
										  const Vec3f & p_up,
										  const float	p_height,
										  const float	p_width )
		: BaseCamera( p_position ), _viewportHeight( p_height ), _viewportWidth( p_width )
	{
		_w = glm::normalize( p_position - p_lookAt );
		_u = glm::normalize( glm::cross( p_up, _w ) );
		_v = glm::normalize( glm::cross( _w, _u ) );
		_updateViewport();
	}

	void OrthographicCamera::_updateViewport()
	{
		_viewportV = _v * _viewportHeight;
		_viewportU = _u * _viewportWidth;

		_viewportTopLeftCorner = _position - ( _w * _focalDistance ) + ( _viewportV * 0.5f ) - ( _viewportU * 0.5f );
	}

} // namespace RT_ISICG
