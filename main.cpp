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

	glClearColor( 0.5f, 0.5f, 0.5f, 0.0f );

	//glEnable( GL_CULL_FACE );

	glEnable( GL_TEXTURE_2D );
	glAlphaFunc( GL_GREATER, 0.0f );
	glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );

	game( window );

	LMP3D::Close();

	return 0;
}

void game( LMP3D::Windows::Window &window )
{
	LMP3D::Graphics::Viewport viewport( LMP3D::Size( WINDOW_WIDTH, WINDOW_HEIGHT ) );
	LMP3D::Graphics::Scene scene;
	LMP3D::Graphics::LoadObjFile( "DATA/lightning.obj", scene );

	scene.getCamera().translate( 0.0f, 30.0f, 50.0f );

	while ( !window.getEvent().quit )
	{
		glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

		window.pollEvent();
		viewport.perspective();
		scene.draw();

		glFlush();
		SDL_GL_SwapBuffers();

		window.fps( 30 );
	}
}
