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

			float x = glm::length( _u );
			float y = glm::length( _v );
			_aire = (x) * (y);
			_n		= glm::normalize(glm::cross( _u, _v ));

			_isSurface = true;
		}

		virtual LightSample sample( const Vec3f & p_point ) const override
		{
			//float _rx = _position.x + ( randomFloat() * _u.x ) + ( randomFloat() * _v.x );
			//float _ry = _position.y + ( randomFloat() * _u.y ) + ( randomFloat() * _v.y );
			//float _rz = _position.z + ( randomFloat() * _u.z ) + ( randomFloat() * _v.z );

			Vec3f randomPosition = _position + _u * randomFloat() + _v * randomFloat(); 
				
			Vec3f _direction = glm::normalize( randomPosition - p_point );
			float _distance	 = glm::distance( randomPosition, p_point );
			float _facteur = glm::pow( _distance, 2.f );
			float cosTheta = glm::max( glm::dot( _n, _direction ), 0.f );
			//float cosTheta	= glm::dot( _direction, _n );
			float _pdf		= ( ( 1.f / _aire ) * ( _facteur / cosTheta ) );
			Vec3f _radiance = ( this->getFlatColor() * this->getPower() ) / _pdf;

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
