#ifndef __RT_ISICG_POINT_LIGHT__
#define __RT_ISICG_POINT_LIGHT__

#include "base_light.hpp"
#include "point_light.hpp"

namespace RT_ISICG
{
	class PointLight : public BaseLight
	{
	  public:
		PointLight()	 = delete;
		virtual ~PointLight() = default;

		PointLight( const Vec3f p_position, const Vec3f & p_color, const float p_power )
			: BaseLight( p_color, p_power )
		{
			_position = p_position;
		}

		virtual LightSample sample(const Vec3f& p_point) const override {
			float _distance = glm::distance( _position, p_point );
			// Vec3f _radiance = glm::inverse( _distance, glm::pow( );
			Vec3f _radiance	 = WHITE;
			Vec3f _direction = p_point - _position;

			LightSample lightSample( _direction, _distance, _radiance, 1.f );
			return lightSample;
		}

	  private:
		Vec3f _position;
	};

} // namespace RT_ISICG

#endif // __RT_ISICG_POINT_LIGHT__
