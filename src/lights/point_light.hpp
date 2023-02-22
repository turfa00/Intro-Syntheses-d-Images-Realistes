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

		PointLight( const Vec3f p_position ) { _position = p_position; }

		void sample() {

		}
	  private:
		Vec3f _position;
	};

} // namespace RT_ISICG

#endif // __RT_ISICG_POINTLIGHT__
