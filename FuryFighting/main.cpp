#include <LMP3D/LMP3D.h>

#include "Game.h"

using namespace FuryFighting;

namespace
{
	static int const WINDOW_WIDTH = 640;
	static int const WINDOW_HEIGHT = 480;
}

LMP3D_INIT_PLATFORM( romdisk );

int main( int argc, char ** argv )
{
	LMP3D::initialise();
	{
		// Scope to prevent the window from being destroyed after call to LMP3D::cleanup
		LMP3D::Windows::Window window( "Fury Fighting", WINDOW_WIDTH, WINDOW_HEIGHT );
		Game game( window );
		game.loop();
	}
	LMP3D::cleanup();
	return 0;
}
