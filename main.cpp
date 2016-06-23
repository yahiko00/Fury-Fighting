#include <SDL/SDL.h>

#include <GL/glew.h>

#ifdef _WIN32
#	undef main
#endif

#include "LMP3D/LMP3D.h"

namespace
{
	static int const WINDOW_WIDTH = 1024;
	static int const WINDOW_HEIGHT = 768;
}

void game( LMP3D::Windows::Window &window );

int main( int argc, char ** argv )
{
	LMP3D::Init();
	LMP3D::Windows::Window window;
	window.setName( "Fury Fighting" );
	window.setSize( WINDOW_WIDTH, WINDOW_HEIGHT );

	game( window );

	LMP3D::Close();

	return 0;
}

void game( LMP3D::Windows::Window &window )
{
	LMP3D::Graphics::Viewport viewport( LMP3D::Size( WINDOW_WIDTH, WINDOW_HEIGHT ) );
	LMP3D::Graphics::Graphics graphics;
	LMP3D::Graphics::Scene scene;
	LMP3D::Graphics::ObjectPtr object = LMP3D::Graphics::loadObjFile( "DATA/lightning.obj", graphics, scene );

	scene.getCamera().translate( 0.0f, 30.0f, 50.0f );
	LMP3D::Graphics::Quaternion rotate( LMP3D::Graphics::Vector3( 0, 1, 0 ), LMP3D::Graphics::radians( 10.0f ) );

	while ( !window.getEvent().quit )
	{
		window.beginFrame();
		object->rotate( rotate );
		window.pollEvent();
		viewport.perspective();
		scene.draw();
		window.endFrame( 30 );
	}
}
