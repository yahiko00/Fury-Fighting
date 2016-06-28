#include "LMP3D.h"

namespace LMP3D
{
	static SDL_Joystick *joystick = NULL;

	void InitLMP3D()
	{
		SDL_Init( SDL_INIT_VIDEO | SDL_INIT_JOYSTICK );

		SDL_ShowCursor( 0 );
		SDL_JoystickEventState( SDL_ENABLE );
		joystick = SDL_JoystickOpen( 0 );

		SDL_WM_SetIcon( NULL, NULL );
	}

	void CloseLMP3D()
	{
		SDL_JoystickClose( joystick );
		SDL_Quit();
	}
}

