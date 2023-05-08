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
			_direction = p_direction;
		}

		virtual LightSample sample( const Vec3f & p_point ) const override
		{
			float _distance	 = glm::distance( _position, p_point );
			float _facteur	 = glm::pow( _distance, 2 );
			//Vec3f _radiance	 = ( this->getFlatColor() * this->getPower() ) / _facteur;
			//Vec3f _direction = glm::normalize( _position - p_point );
			float angle = glm::max( glm::dot( p_point, _direction ), 0.f );
			float _pdf		= ( _facteur / angle );
			Vec3f _radiance = ( this->getFlatColor() * this->getPower() ) / _pdf;
			if (angle < _cutoff) {
				LightSample lightSample( _direction, _distance, _radiance, _pdf );
				return lightSample;
			}
			//float _pdf		 = 1.f;

			LightSample lightSample( _direction, _distance, Vec3f(0.f), _pdf );
			return lightSample;
		}

		inline const Vec3f & getPosition() const { return _position; }

	  private:
		Vec3f _position;
		Vec3f _direction;
		float _cutoff = 20.f;
	};

} // namespace RT_ISICG

#endif // __RT_ISICG_SPOT_LIGHT__
