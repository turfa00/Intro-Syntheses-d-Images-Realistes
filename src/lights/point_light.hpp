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

		PointLight( const Vec3f p_position ) : BaseLight(Vec3f(1.f, 1.f, 1.f), 1.f )
		{
			_position = p_position;
		}

		LightSample sample( const Vec3f & p_point ) {
			//this._radiance =
			float _distance = glm::distance( _position, p_point );
			Vec3f _radiance = glm::inverse( _distance );
			Vec3f _direction = p_point - _position;

			LightSample lightSample(_direction, _distance, _radiance, 1.f);
			return lightSample;
		}
	  private:
		Vec3f _position;
	};

} // namespace RT_ISICG

#endif // __RT_ISICG_POINTLIGHT__
