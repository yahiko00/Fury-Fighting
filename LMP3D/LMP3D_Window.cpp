#include "LMP3D_Window.h"

#include <SDL/SDL.h>

namespace LMP3D
{
	namespace Windows
	{
		Window::Window()
		{
		}

		Window::~Window()
		{
		}

		void Window::setName( const char *name )
		{
			SDL_WM_SetCaption( "Fury Fighting", nullptr );
		}

		void Window::setSize( int w, int h )
		{
			SDL_SetVideoMode( w, h, 24, SDL_OPENGL );
		}

		void Window::pollEvent()
		{
			SDL_Event sevent;

			event.clikdroit = 0;
			event.clikgauche = 0;
			event.quit = 0;

			for ( int i = 0; i < 350; i++ )
			{
				if ( event.touche[i] == 1 )
				{
					event.touche[i] = 2;
				}
				else
				{
					event.touche[i] = 0;
				}
			}

			while ( SDL_PollEvent( &sevent ) == 1 )
			{
				switch ( sevent.type )
				{
				case SDL_MOUSEMOTION :
					event.sourisx = sevent.motion.x;
					event.sourisy = sevent.motion.y;
				break;

				case SDL_QUIT:
					event.quit = 1;
				break;

				case SDL_MOUSEBUTTONDOWN:
					switch ( sevent.button.button )
					{
					case SDL_BUTTON_RIGHT:
						event.clikdroit = 1;
					break;

					case SDL_BUTTON_LEFT:
						event.clikgauche = 1;
					break;
					}
				break;

				case SDL_MOUSEBUTTONUP:
					switch ( sevent.button.button )
					{
					case SDL_BUTTON_RIGHT:
						event.clikdroit = 3;
					break;

					case SDL_BUTTON_LEFT:
						event.clikgauche = 3;
					break;
					}
				break;

				case SDL_KEYDOWN:
					for ( int i = 0; i < 325; i++ )
					{
						if(sevent.key.keysym.sym == i)
						{
							event.touche[i] = 1;

							//event.key[MNSK_KEYA] = i;
							//event.key_ext[MNSK_KEYA] = i;
						}
					}
				break;

				case SDL_KEYUP:
					for ( int i = 0; i < 325; i++ )
					{
						if ( sevent.key.keysym.sym == i )
						{
							event.touche[i] = 3;
						}
					}
					//event.key_ext[MNSK_KEYA] = -1;
				break;
				}
			}
		}

		void Window::fps( int fps )
		{
			int t = 0;
			int slp = 1000 / fps;

			time_a = SDL_GetTicks();
			t = time_a - time_b;

			if ( t <= 0 )
			{
				t = 0;
			}

			if ( t >= slp )
			{
				t = slp - 1;
			}

			SDL_Delay( slp - t );
			time_b = SDL_GetTicks();
		}
	}
}
