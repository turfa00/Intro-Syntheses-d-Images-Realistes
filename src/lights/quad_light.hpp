#ifndef __RT_ISICG_QUAD_LIGHT__
#define __RT_ISICG_QUAD_LIGHT__

#include "base_light.hpp"
#include "../utils/random.hpp"


namespace RT_ISICG
{
	class QuadLight : public BaseLight
	{
	  public:
		QuadLight()			  = delete;
		virtual ~QuadLight() = default;

		QuadLight( const Vec3f							p_position,
				   const Vec3f							p_u,
				   const Vec3f							p_v,
				   const Vec3f							& p_color,
				   const float							p_power )
			: BaseLight( p_color, p_power )
		{
			_position = p_position;
			_u		  = p_u;
			_v		  = p_v;

			//_aire = () * ();
		}

		virtual LightSample sample( const Vec3f & p_point ) const override
		{
			float _rx = _position.x + (randomFloat() * glm::sign(_u.x));
			float _ry = _position.y + (randomFloat() * glm::sign( _v.y ));

			Vec3f rPosition = Vec3f(_rx, _ry, _position.z);
			Vec3f _direction = glm::normalize( p_point - rPosition );
			//Vec3f _direction = glm::normalize( p_point - _position );
			float _distance	 = glm::distance( _position, p_point );
			float _facteur	 = 1 / glm::pow( _distance, 2 );
			float _pdf		 = ( ( 1 / _aire ) * _facteur )
						 / ( glm::dot( _n, _direction ) / glm::length( _u ) * glm::length( _direction ) );
			Vec3f _radiance = ( this->getFlatColor() * this->getPower() ) / _pdf;


			// float _distance = glm::distance( _position, p_point);
			// float _facteur	 = glm::pow( 1 / _distance, 2 );
			//Vec3f _direction = glm::normalize( p_point - _position );

			LightSample lightSample( _direction, _distance, _radiance, _pdf );
			return lightSample;
		}

		inline const Vec3f & getPosition() const { return _position; }

	  private:
		Vec3f _position, _n;
		Vec3f _u, _v;
		float _aire;
	};

} // namespace RT_ISICG

#endif // __RT_ISICG_QUAD_LIGHT__
