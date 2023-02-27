#ifndef __RT_ISICG_BASE_LIGHT__
#define __RT_ISICG_BASE_LIGHT__

#include "light_sample.hpp"
#include "../defines.hpp"

namespace RT_ISICG
{
	class BaseLight
	{
	  public:
		BaseLight( const Vec3f & p_color, const float p_power ) : _color( p_color ), _power(p_power){}
		virtual ~BaseLight() = default;

		inline const Vec3f & getFlatColor() const { return _color; }
		inline const float & getPower() const { return _power; }
		inline const Vec3f & getPosition() const;

		virtual LightSample sample( const Vec3f & p_point ) const = 0;
		inline const bool & getIsSurface() const { return _isSurface; }

	  protected:
		// TODO: give a name, like objects and materials
		const std::string _name;
		Vec3f _color = WHITE;
		float _power	 = 1.f;
		bool			  _isSurface = true;
	};

} // namespace RT_ISICG

#endif // __RT_ISICG_BASE_LIGHT__
