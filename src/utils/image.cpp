#include "image.hpp"
#include <iostream>

#ifndef STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#endif
#include "stb/stb_image.h"

namespace RT_ISICG
{
	Image::~Image() { stbi_image_free( _pixels ); }

	bool Image::load( const std::string & p_path )
	{
		//_pixels = stbi_load( p_filePath.c_str(), &_width, &_height, &_nbChannels, 0 );
		_pixels = stbi_load( p_path.c_str(), &_width, &_height, &_nbChannels, 0 );
		if ( _pixels == nullptr )
		{
			std::cerr << "[ERROR] - Failed to load texture " << p_filePath << std::endl;
			std::cerr << "=> " << stbi_failure_reason << std::endl;
		} 
		return _pixels != nullptr;
	}
} // namespace RT_ISICG
