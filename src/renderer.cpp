#include "renderer.hpp"
#include "integrators/ray_cast_integrator.hpp"
#include "integrators/direct_lighting_integrator.hpp"
#include "utils/console_progress_bar.hpp"
#include "utils/random.hpp"

namespace RT_ISICG
{
	Renderer::Renderer() { _integrator = new RayCastIntegrator(); }

	void Renderer::setIntegrator( const IntegratorType p_integratorType )
	{
		if ( _integrator != nullptr ) { delete _integrator; }

		switch ( p_integratorType )
		{
		case IntegratorType::RAY_CAST:
		default:
		{
			_integrator = new RayCastIntegrator();
			break;
		}

		case IntegratorType::COUNT: 
			_integrator = new DirectLightingIntegrator(); 
			break;
		}
	}

	void Renderer::setBackgroundColor( const Vec3f & p_color )
	{
		if ( _integrator == nullptr ) { std::cout << "[Renderer::setBackgroundColor] Integrator is null" << std::endl; }
		else
		{
			_integrator->setBackgroundColor( p_color );
		}
	}

	float Renderer::renderImage( const Scene & p_scene, const BaseCamera * p_camera, Texture & p_texture )
	{
		const int width	 = p_texture.getWidth();
		const int height = p_texture.getHeight();

		Chrono			   chrono;
		ConsoleProgressBar progressBar;

		progressBar.start( height, 50 );
		chrono.start();

		//Rays

		//PerspectiveCamera camera( Vec3f( 0.f, 0.f, -1.f ), Vec3f( 0.f, 0.f, 0.f ), Vec3f( 0.f, 1.f, 0.f ), 45.f, 1.5f );

		//Color
		Vec3f color, rayColor;
		float x, y, offsetx, offsety;
		#pragma omp parallel for
		for ( int j = 0; j < height; j++ )
		{
			for ( int i = 0; i < width; i++ )
			{
				
				//x = (float) i / (width-1);
				//y = (float) j / (height-1);
				//Ray ray = p_camera->generateRay( x, y );
				rayColor = Vec3f( 0.f, 0.f, 0.f );
				
				
				for (int k = 0; k < _nbPixelSamples; k++) {
					offsetx = randomFloat();
					offsety = randomFloat();
					x = (float) ((i + offsetx) / ( width - 1 ));
					y = (float) ((j + offsety) / ( height - 1 ));

					Ray ray = p_camera->generateRay( x, y );
					rayColor += _integrator->Li( p_scene, ray, 0.f, 1000.f );
				}
				rayColor /= _nbPixelSamples;
				//color	= Vec3f(rayColor.x / _nbPixelSamples, rayColor.y / _nbPixelSamples, rayColor.z / _nbPixelSamples);
				//Ray ray = p_camera->generateRay( x, y );
				//std::cout << color.x << color.y << color.z << std::endl; 
				//Ray ray = p_camera->generateRay( x, y );
				
				//color = _integrator->Li( p_scene, ray, 0.f, std::numeric_limits<float>::max() );
				//color = glm::clamp( _integrator->Li( p_scene, ray, 0.f, std::numeric_limits<float>::max() ), 0.f, 255.f );
				//color	= ( ray.getDirection() + 1.f ) * 0.5f;
				p_texture.setPixel( i, j, rayColor );
			}
			progressBar.next();
		}

		chrono.stop();
		progressBar.stop();

		return chrono.elapsedTime();
	}
} // namespace RT_ISICG
