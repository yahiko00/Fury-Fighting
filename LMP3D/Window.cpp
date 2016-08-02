#include "Window.h"

#include <SDL/SDL.h>

#include <cstring>

#include "Platform.h"
#include "Graphics/Platform.h"
#include "Graphics/Graphics.h"

namespace LMP3D
{
	namespace Windows
	{
		namespace
		{
			void doOnKey( SDLKey key, Event & event, State state )
			{
				typedef std::map< SDLKey, Button > ButtonKeyMap;
				static ButtonKeyMap map;

				if ( map.empty() )
				{
					map.insert( std::make_pair( SDLK_UP, Button_DPadUp ) );
					map.insert( std::make_pair( SDLK_DOWN, Button_DPadDown ) );
					map.insert( std::make_pair( SDLK_LEFT, Button_DPadLeft ) );
					map.insert( std::make_pair( SDLK_RIGHT, Button_DPadRight ) );
					map.insert( std::make_pair( SDLK_a, Button_A ) );
					map.insert( std::make_pair( SDLK_z, Button_B ) );
					map.insert( std::make_pair( SDLK_e, Button_C ) );
					map.insert( std::make_pair( SDLK_r, Button_D ) );
					map.insert( std::make_pair( SDLK_PAGEUP, Button_R2 ) );
					map.insert( std::make_pair( SDLK_PAGEDOWN, Button_R1 ) );
					map.insert( std::make_pair( SDLK_INSERT, Button_L2 ) );
					map.insert( std::make_pair( SDLK_DELETE, Button_L1 ) );
					map.insert( std::make_pair( SDLK_RETURN, Button_Start ) );
					map.insert( std::make_pair( SDLK_ESCAPE, Button_Select ) );
				}

				ButtonKeyMap::iterator it = map.find( key );

				if ( it != map.end() )
				{
					event.buttonState[it->second] = state;
				}
			}
		}

		Window::Window( const char * name, int w, int h )
			: m_savedTime( 0u )
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
			static State leftState = State_Released;
			static State rightState = State_Released;
			static Position previous;

			m_event.quit = 0;
			m_event.leftAxisState.x = 0;
			m_event.leftAxisState.y = 0;
			m_event.rightAxisState.x = 0;
			m_event.rightAxisState.y = 0;

			for ( int i = 0; i < Button_Count; i++ )
			{
				if ( m_event.buttonState[i] >= State_Pressed )
				{
					m_event.buttonState[i] = State_Held;
				}
				else
				{
					m_event.buttonState[i] = State_Released;
				}
			}

			SDL_Event event;

			while ( SDL_PollEvent( &event ) == 1 )
			{
				switch ( event.type )
				{
				case SDL_MOUSEMOTION:
					if ( leftState == State_Pressed )
					{
						m_event.leftAxisState.x = event.motion.x - previous.x;
						m_event.leftAxisState.y = event.motion.y - previous.y;
					}
					if ( rightState == State_Pressed )
					{
						m_event.rightAxisState.x = event.motion.x - previous.x;
						m_event.rightAxisState.y = event.motion.y - previous.y;
					}
					previous.x = event.motion.x;
					previous.y = event.motion.y;
					break;

				case SDL_QUIT:
					m_event.quit = 1;
					break;

				case SDL_MOUSEBUTTONDOWN:
					switch ( event.button.button )
					{
					case SDL_BUTTON_RIGHT:
						rightState = State_Pressed;
						break;

					case SDL_BUTTON_LEFT:
						leftState = State_Pressed;
						break;
					}
					break;

				case SDL_MOUSEBUTTONUP:
					switch ( event.button.button )
					{
					case SDL_BUTTON_RIGHT:
						rightState = State_Released;
						break;

					case SDL_BUTTON_LEFT:
						leftState = State_Released;
						break;
					}
					break;

				case SDL_KEYDOWN:
					doOnKey( event.key.keysym.sym, m_event, State_Pressed );
					break;

				case SDL_KEYUP:
					doOnKey( event.key.keysym.sym, m_event, State_Released );
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
			Platform::endFrame( fps, m_savedTime );
		}
	}
}
