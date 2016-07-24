#include "LMP3D/LMP3D.h"

using namespace LMP3D;

namespace
{
	static int const WINDOW_WIDTH = 640;
	static int const WINDOW_HEIGHT = 480;
}

LMP3D_INIT_PLATFORM( romdisk );

void game( Windows::Window & window );

int main( int argc, char ** argv )
{
	LMP3D::initialise();
	{
		// Scope to prevent the window from being destroyed after call to LMP3D::cleanup
		Windows::Window window( "Fury Fighting", WINDOW_WIDTH, WINDOW_HEIGHT );
		game( window );
	}
	LMP3D::cleanup();
	return 0;
}

void game( Windows::Window & window )
{
	Graphics::Viewport viewport( Size( WINDOW_WIDTH, WINDOW_HEIGHT ) );
	Graphics::Scene scene;
	Graphics::ObjectPtr object = scene.createObject( LMP3D::getDataDirectory() + PATH_SEPARATOR + "Tidus.obj" );

	scene.getCamera().translate( 0.0f, 1.0f, 5.0f );
	Graphics::Quaternion rotate( Graphics::Vector3( 0, 1, 0 ), Graphics::radians( 10.0f ) );
	Graphics::Quaternion rotate2( Graphics::Vector3( 0, 1, 0 ), Graphics::radians( -10.0f ) );
	size_t count = 0u;
	Graphics::ObjectPtr clone = NULL;

	while ( !window.getEvent().quit )
	{
		window.beginFrame();
		object->rotate( rotate );
		object->translate( 0, -0.05f, -0.1f );
		window.pollEvent();
		viewport.perspective();
		scene.draw();

		if ( count == 100 )
		{
			clone = object->clone();
			++count;
		}
		else if ( count < 100 )
		{
			++count;
		}
		else
		{
			clone->rotate( rotate2 );
			clone->translate( -0.05f, 0, -0.1f );
		}

		window.endFrame( 30 );
	}
}
