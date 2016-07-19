#include "LMP3D_Window.h"

#include <SDL/SDL.h>

#include <cstring>

#include "Platform.h"
#include "Graphics/Platform.h"
#include "Graphics/Graphics.h"

namespace LMP3D
{
	namespace Windows
	{
		Event::Event()
			: sourisx( 0 )
			, sourisy( 0 )
			, quit( 0 )
			, clikdroit( 0 )
			, clikgauche( 0 )
		{
			std::memset( touche, 0, sizeof( touche ) );
		}

		Window::Window( const char * name, int w, int h )
			: savedTime( 0u )
		{
			Platform::initialiseWindow( name, w, h );
			Graphics::Platform::initialiseWindow();
		}

		Window::~Window()
		{
			Graphics::Platform::cleanupWindow();
			Platform::cleanupWindow();
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

		void Window::beginFrame()
		{
			Graphics::Platform::clearFrame();
		}

		void Window::endFrame( int fps )
		{
			Graphics::Platform::flushFrame();
			Platform::endFrame( fps, savedTime );
		}
	}
}
