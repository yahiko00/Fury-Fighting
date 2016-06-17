#include <SDL/SDL.h>

#include <GL/glew.h>

#ifdef _WIN32
#	undef main
#endif

#include "LMP3D/LMP3D.h"
#include "LMP3D/LMP3D_Window.h"

void game( LMP3D::Windows::Window &window );

int main( int argc, char ** argv )
{
	LMP3D::Init();
	LMP3D::Windows::Window window;
	window.setName("Fury Fighting");
	window.setSize(640, 480);

	glClearColor( 0.5, 0.5, 0.5, 0 );

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
	while( !window.getEvent().quit )
	{
		glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

		window.pollEvent();

		glFlush();
		SDL_GL_SwapBuffers();

		window.fps( 30 );
	}
}
