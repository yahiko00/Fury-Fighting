#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <SDL/SDL.h>

#include <GL/glew.h>

#include "MNS/MNS.h"

#ifdef _WIN32
#	undef main
#endif

#include "LMP3D/LMP3D.h"

LMP3D::Windows windows;

void game();

int main( void )
{

    LMP3D::Init();
    windows.setName("Fury Fighting");
    windows.setSize(640, 480);


	glClearColor( 0.5, 0.5, 0.5, 0 );

	//glEnable(GL_CULL_FACE);

	glEnable( GL_TEXTURE_2D );
	glAlphaFunc( GL_GREATER, 0.0f );
	glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );

	game();

    LMP3D::Close();

	return 0;
}

void game()
{

    windows.initEvent();
	while(windows.event.quit == 0)
	{
		glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

        windows.getEvent();

		glFlush();
		SDL_GL_SwapBuffers();

		windows.fps(30);
	}
}

