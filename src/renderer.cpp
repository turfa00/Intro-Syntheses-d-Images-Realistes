#include "renderer.hpp"
#include "integrators/ray_cast_integrator.hpp"
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
		Vec3f color;
		float x, y;
		for ( int j = 0; j < height; j++ )
		{
			for ( int i = 0; i < width; i++ )
			{
				//Ray ray( p_camera->getPosition(), Vec3f( i, j, 1.f ) );
				Ray ray = p_camera->generateRay( i, j );
				color = (ray.getDirection() + 1.f) * 0.5f;
				x = (float) i / (width-1);
				y = (float) j / (height-1);
				//p_texture.setPixel( i, j, Vec3f(x, y , 0.f) );
				p_texture.setPixel( i, j, color );
			}
			progressBar.next();
		}

		chrono.stop();
		progressBar.stop();

		return chrono.elapsedTime();
	}
} // namespace RT_ISICG
