#include <SDL/SDL.h>

#include <GL/glew.h>

#ifdef _WIN32
#	undef main
#endif

#include "LMP3D/LMP3D.h"

namespace
{
	static int const WINDOW_WIDTH = 640;
	static int const WINDOW_HEIGHT = 480;
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
	LMP3D::Graphics::Viewport viewport( LMP3D::Graphics::Size( WINDOW_WIDTH, WINDOW_HEIGHT ) );
	LMP3D::Graphics::Camera camera;
	LMP3D::Graphics::MaterialMap materials;
	LMP3D::Graphics::Object object = LMP3D::Graphics::LoadObjFile( "DATA/lightning.obj", materials );

	camera.translate( -50.0f, 0.0f, 0.0f );

	while ( !window.getEvent().quit )
	{
		glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

		window.pollEvent();
		viewport.perspective();
		camera.bind();
		object.draw();
		camera.unbind();

		glFlush();
		SDL_GL_SwapBuffers();

		window.fps( 30 );
	}

	for ( LMP3D::Graphics::MaterialMap::iterator it = materials.begin(); it != materials.end(); ++it )
	{
		delete it->second;
	}
}
