#if !defined( _arch_dreamcast ) && !defined( _PS2 )

#include "SDL.h"

#include "../StringUtils.h"
#include "../FileUtils.h"

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <cstring>

#ifdef _WIN32
#	include <Windows.h>
#	undef main
#else
#	include <unistd.h>
#endif

#include "LMP3D/Graphics/Platform.h"

namespace LMP3D
{
	namespace Platform
	{
		static SDL_Joystick * joystick = NULL;

		void initialise()
		{
			SDL_Init( SDL_INIT_VIDEO | SDL_INIT_JOYSTICK );
			SDL_ShowCursor( 0 );
			SDL_JoystickEventState( SDL_ENABLE );
			SDL_WM_SetIcon( NULL, NULL );
			joystick = SDL_JoystickOpen( 0 );
		}

		void cleanup()
		{
			SDL_JoystickClose( joystick );
			SDL_Quit();
		}

		void initialiseWindow( const char * name, int w, int h )
		{
			SDL_WM_SetCaption( name, NULL );
			SDL_SetVideoMode( w, h, 24, SDL_OPENGL );
		}

		void cleanupWindow()
		{
		}

		void endFrame( int fps, unsigned int & savedTime )
		{
			SDL_GL_SwapBuffers();

			int t = 0;
			int slp = 1000 / fps;

			unsigned int currentTime = SDL_GetTicks();
			t = currentTime - savedTime;

			if ( t <= 0 )
			{
				t = 0;
			}

			if ( t >= slp )
			{
				t = slp - 1;
			}

			SDL_Delay( slp - t );
			savedTime = SDL_GetTicks();
		}

		bool loadImage( std::string const & filePath, ImageData & data )
		{
			bool ret = false;
			pointer< SDL_Surface > image( IMG_Load( filePath.c_str() ), SDL_FreeSurface );

			if ( image )
			{
				if ( image->format->BytesPerPixel == 3 )
				{
					if ( image->format->Rmask > image->format->Gmask )
					{
						data.format = BGR;
					}
					else
					{
						data.format = RGB;
					}
				}
				else if ( image->format->BytesPerPixel == 4 )
				{
					if ( image->format->Rmask > image->format->Gmask )
					{
						data.format = BGRA;
					}
					else
					{
						data.format = RGBA;
					}
				}

				uint8_t * buffer = reinterpret_cast< uint8_t * >( image->pixels );
				data.size = Size( image->w, image->h );
				data.data.insert( data.data.end(), buffer, buffer + image->pitch * image->h );
				ret = true;
			}

			return ret;
		}

		std::string getCurrentDirectory()
		{
			std::string l_pathReturn;

#if defined( _WIN32 )

			char l_path[FILENAME_MAX] = { 0 };
			DWORD l_result = ::GetModuleFileNameA( NULL, l_path, sizeof( l_path ) );

			if ( l_result != 0 )
			{
				l_pathReturn = l_path;
			}

#elif defined( __linux__ )

			char l_path[FILENAME_MAX] = { 0 };
			char l_buffer[32];
			sprintf( l_buffer, "/proc/%d/exe", getpid() );
			int l_bytes = std::min< std::size_t >( readlink( l_buffer, l_path, sizeof( l_path ) ), sizeof( l_path ) - 1 );

			if ( l_bytes > 0 )
			{
				l_path[l_bytes] = '\0';
				l_pathReturn = l_path;
			}

#else

#	error "Unsupported platform"

#endif

			l_pathReturn = getFilePath( l_pathReturn );
			return l_pathReturn;
		}

		std::string getDataDirectory()
		{
			return getCurrentDirectory() / "Data";
		}
	}
}

#endif
