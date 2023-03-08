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
		case IntegratorType::DIRECT_LIGHTING: 
			_integrator = new DirectLightingIntegrator(); 
			break;
		//case IntegratorType::COUNT: 

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

		#pragma omp parallel for
		for ( int j = 0; j < height; j++ )
		{
			for ( int i = 0; i < width; i++ )
			{
				Vec3f rayColor = VEC3F_ZERO;
				//Without anti aliasing
				float x	 = (float)i / ( width - 1 );
				float y	  = (float)j / ( height - 1 );
				Ray ray	 = p_camera->generateRay( x, y );
				rayColor = _integrator->Li( p_scene, ray, 0.f, 10000.f );

				//With anti aliasing
				/* for ( int k = 0; k < _nbPixelSamples; k++ )
				{
					
					offsetx = randomFloat() - randomFloat();
					offsety = randomFloat() - randomFloat();
					x = ((float) i + offsetx ) / ( width - 1 );
					y =	((float) j + offsety ) / ( height - 1 );

					Ray ray = p_camera->generateRay( x, y );
					//rayColor += _integrator->Li( p_scene, ray, 0.f, 1000.f );
					rayColor += _integrator->Li( p_scene, ray, 0.f, 1000000.f );
				}
				rayColor /= _nbPixelSamples;*/
				p_texture.setPixel( i, j, rayColor );
			}
			progressBar.next();
		}

		chrono.stop();
		progressBar.stop();

		return chrono.elapsedTime();
	}
} // namespace RT_ISICG
