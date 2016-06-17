#include "LMP3D.h"

namespace LMP3D
{
	static SDL_Joystick *joystick = NULL;

	void Init()
	{
		SDL_Init( SDL_INIT_VIDEO | SDL_INIT_JOYSTICK );

		SDL_ShowCursor( 0 );
		SDL_JoystickEventState( SDL_ENABLE );
		joystick = SDL_JoystickOpen( 0 );

		SDL_WM_SetIcon( NULL, NULL );
	}

	void Close()
	{
		SDL_JoystickClose( joystick );
		SDL_Quit();
	}
}

