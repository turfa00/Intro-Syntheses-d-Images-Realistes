#include "cameras/perspective_camera.hpp"
#include "objects/sphere.hpp"
#include "defines.hpp"
#include "renderer.hpp"

namespace RT_ISICG
{
	int main( int argc, char ** argv )
	{
		const int imgWidth	= 600;
		const int imgHeight = 400;

		// Create a texture to render the scene.
		Texture img = Texture( imgWidth, imgHeight );

		// Create and init scene.
		Scene scene;
		scene.init();

		// Create a perspective camera.
		//PerspectiveCamera camera( float( imgWidth ) / imgHeight );
		Vec3f			  position = Vec3f( 0, 0, -2 );
		Vec3f			  lookAt   = Vec3f( 0, 0, 79);
		Vec3f			  up	   = Vec3f( 0, 1, 0 );
		float			  fov	   = 60.f;
		float			  aspectRatio = float (imgWidth / imgHeight);

		PerspectiveCamera camera( position, lookAt, up, fov, aspectRatio );

		// Create and setup the renderer.
		Renderer renderer;
		renderer.setNbPixelSamples( 32 );
		//renderer.setIntegrator( IntegratorType::RAY_CAST ); //A
		renderer.setIntegrator( IntegratorType::COUNT );
		renderer.setBackgroundColor( GREY );

		// Launch rendering.
		std::cout << "Rendering..." << std::endl;
		std::cout << "- Image size: " << imgWidth << "x" << imgHeight << std::endl;

		float renderingTime = renderer.renderImage( scene, &camera, img );

		std::cout << "-> Done in " << renderingTime << "ms" << std::endl;

		// Save rendered image.
		const std::string imgName = "image.jpg";
		img.saveJPG( RESULTS_PATH + imgName );

		return EXIT_SUCCESS;
	}
} // namespace RT_ISICG

int main( int argc, char ** argv )
{
	try
	{
		return RT_ISICG::main( argc, argv );
	}
	catch ( const std::exception & e )
	{
		std::cerr << "Exception caught:" << std::endl << e.what() << std::endl;
	}
}
