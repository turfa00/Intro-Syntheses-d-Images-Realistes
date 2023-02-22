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
			float _distance = glm::distance( _position, p_point);
			float _facteur	 = 1 / pow( _distance, 2 );
			Vec3f _radiance = ( this->getFlatColor() * this->getPower() ) / _facteur;
			Vec3f _direction = glm::normalize(p_point - _position);

			LightSample lightSample( _direction, _distance, _radiance, 1.f );
			return lightSample;
		}

	  private:
		Vec3f _position;
	};

} // namespace RT_ISICG

#endif // __RT_ISICG_POINT_LIGHT__
