#ifndef __RT_ISICG_SPOT_LIGHT__
#define __RT_ISICG_SPOT_LIGHT__

#include "base_light.hpp"

namespace RT_ISICG
{
	class SpotLight : public BaseLight
	{
	  public:
		SpotLight()			  = delete;
		virtual ~SpotLight() = default;

		SpotLight( const Vec3f p_position, const Vec3f & p_direction, const Vec3f & p_color, const float p_power )
			: BaseLight( p_color, p_power )
		{
			_position = p_position;
			_direction = glm::normalize(p_direction);
		}

		virtual LightSample sample( const Vec3f & p_point ) const override
		{
			float _distance	 = glm::distance( _position, p_point );
			Vec3f _directionToPoint = glm::normalize( _position - p_point );
			float _facteur	 = glm::pow( _distance, 1.8 );
			float angle			= glm::degrees(glm::max( glm::dot( _direction, _directionToPoint ), 0.f ));
			Vec3f _radiance = ( this->getFlatColor() * this->getPower() ) / _facteur;
			if ( angle > _openingAngle )
			{
				
				LightSample lightSample( _direction, _distance, _radiance, 1.f );
				return lightSample;
			}
			_radiance = ( this->getFlatColor() * angle / _facteur);
			LightSample lightSample( _direction, _distance, _radiance, 1.f );
			return lightSample;
		}

		inline const Vec3f & getPosition() const { return _position; }

	  private:
		Vec3f _position;
		Vec3f _direction;
		float _openingAngle = 45.f;
	};

} // namespace RT_ISICG

#endif // __RT_ISICG_SPOT_LIGHT__
