#ifndef __RT_ISICG_TEXTURE_MATERIAL__
#define __RT_ISICG_TEXTURE_MATERIAL__

#include "base_material.hpp"
#include "defines.hpp"
//#include "utils/image.hpp"
#include "utils/stb_image/stb_image.h"
//#include "utils/stb_image/rtw_stb_image.h"

//#define STB_IMAGE_IMPLEMENTATION
//#include "utils/stb_image/stb_image.h"
//#define STB_IMAGE_WRITE_IMPLEMENTATION
//#include "utils/stb_image/stb_image_write.h"


namespace RT_ISICG
{
	class TextureMaterial : public BaseMaterial
	{
	  public:
		//TextureMaterial( const std::string & p_name, const FilePath & p_filePath ) : BaseMaterial( p_name )
		TextureMaterial( const std::string & p_name, const std::string & p_path ) : BaseMaterial( p_name )
		{
			const char * filePath = p_path.c_str();
			_pixels		= stbi_load( filePath, &_width, &_height, &_nbChannels, _nbChannels );
		}

		virtual ~TextureMaterial() = default;
		Vec3f shade( const Ray & p_ray, const HitRecord & p_hit, const LightSample & p_lightSample ) const // override
		{
			return _color;
		}

		Vec3f				 color(float u, float v, const Vec3f& p) { 
			u = glm::clamp( u, 0.f, 1.f );
			v = glm::clamp( v, 0.f, 1.f );

			int i = u * _width;
			int j = v * _height;

			if (i >= _width) { i = _width - 1;
			}

			if (j >= _height) { j = _height - 1;
			}

			_color = Vec3f( scale * _pixels[ 0 ], scale * _pixels[ 1 ], scale * _pixels[ 2 ] );

			return _color;
		}
		inline const Vec3f & getFlatColor() const override { return _color; }
	  protected:
		Vec3f _color = Vec3f( 1.f, 1.f, 1.f );
		int	  _width = 0, _height = 0, _nbChannels = 3;
		unsigned char * _pixels		= nullptr;
		float			u = 0.f, v = 0.f, scale = 1.f / 255.f;
	};

} // namespace RT_ISICG

#endif // __RT_ISICG_COLOR_MATERIAL__
