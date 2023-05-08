#ifndef __RT_ISICG_TEXTURE_MATERIAL__
#define __RT_ISICG_TEXTURE_MATERIAL__

#include "base_material.hpp"
#include "defines.hpp"
#include "utils/image.hpp"

//#define STB_IMAGE_IMPLEMENTATION
//#include "utils/stb_image/stb_image.h"
//#define STB_IMAGE_WRITE_IMPLEMENTATION
//#include "utils/stb_image/stb_image_write.h"


namespace RT_ISICG
{
	class TextureMaterial : public BaseMaterial
	{
	  public:
		TextureMaterial( const std::string & p_name, const FilePath & p_filePath ) : BaseMaterial( p_name )
		{
			Image _textureImage;
			_textureImage.load( p_filePath );
			_width = _textureImage._width;
			_height = _textureImage._height;
			_nbChannels = _textureImage._nbChannels;
			_pixels = _textureImage._pixels;
		}

		virtual ~TextureMaterial() = default;
		Vec3f shade( const Ray & p_ray, const HitRecord & p_hit, const LightSample & p_lightSample ) const // override
		{
			return _color;
		}

		Vec3f				 color(float u, float v, const Vec3f& p) { 
			return _color;
		}
		inline const Vec3f & getFlatColor() const override { return _color; }
	  protected:
		Vec3f _color = Vec3f( 1.f, 1.f, 1.f );
		int	  _width = 0, _height = 0, _nbChannels = 0;
		unsigned char * _pixels		= nullptr;
		float			u = 0.f, v = 0.f;
	};

} // namespace RT_ISICG

#endif // __RT_ISICG_COLOR_MATERIAL__
