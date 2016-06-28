#include <SDL/SDL.h>

#ifdef _WIN32
#	undef main
#endif

#include "LMP3D/LMP3D.h"

using namespace LMP3D;

namespace
{
	static int const WINDOW_WIDTH = 1024;
	static int const WINDOW_HEIGHT = 768;
}

void game( Windows::Window &window );

int main( int argc, char ** argv )
{
	InitLMP3D();
	{
		// Scope to prevent the window from being destroyed after call to CloseLMP3D
		Windows::Window window( "Fury Fighting", WINDOW_WIDTH, WINDOW_HEIGHT );
		game( window );
	}
	CloseLMP3D();

	return 0;
}

void game( Windows::Window &window )
{
	Graphics::Viewport viewport( Size( WINDOW_WIDTH, WINDOW_HEIGHT ) );
	Graphics::Scene scene;
	Graphics::ObjectPtr object = Graphics::Object::create( "DATA/lightning.obj" );
	scene.addObject( object );

	scene.getCamera().translate( 0.0f, 30.0f, 50.0f );
	Graphics::Quaternion rotate( Graphics::Vector3( 0, 1, 0 ), Graphics::radians( 10.0f ) );
	Graphics::Quaternion rotate2( Graphics::Vector3( 0, 1, 0 ), Graphics::radians( -10.0f ) );
	size_t count = 0u;
	Graphics::ObjectPtr clone = NULL;

	while ( !window.getEvent().quit )
	{
		window.beginFrame();
		object->rotate( rotate );
		object->translate( 0, 0.5f, -1 );
		window.pollEvent();
		viewport.perspective();
		scene.draw();

		if ( count == 100 )
		{
			clone = object->clone();
			scene.addObject( clone );
			++count;
		}
		else if ( count < 100 )
		{
			++count;
		}
		else
		{
			clone->rotate( rotate2 );
			clone->translate( -0.5f, 0, -1 );
		}

		window.endFrame( 30 );
	}
}
