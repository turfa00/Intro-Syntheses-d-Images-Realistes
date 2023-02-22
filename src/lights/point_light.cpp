#include "point_light.hpp"

namespace RT_ISICG
{
	LightSample PointLight::sample( const Vec3f & p_point )
	{
		float _distance = glm::distance( _position, p_point );
		// Vec3f _radiance = glm::inverse( _distance, glm::pow( );
		Vec3f _radiance	 = WHITE;
		Vec3f _direction = p_point - _position;

		LightSample lightSample( _direction, _distance, _radiance, 1.f );
		return lightSample;
	}

} // namespace RT_ISICG