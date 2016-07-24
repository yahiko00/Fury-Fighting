#ifndef ___LMP3D_SDL_H___
#define ___LMP3D_SDL_H___

#include "../Common.h"
#include "../StringUtils.h"
#include "../FileUtils.h"

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <cstring>

#ifdef _WIN32
#	include <direct.h>
#	define GetCurrentDir _getcwd
#	undef main
#else
#	include <unistd.h>
#	define GetCurrentDir getcwd
#endif

#include "LMP3D/Graphics/Platform.h"

#define LMP3D_INIT_PLATFORM( rom )

namespace LMP3D
{
	namespace Platform
	{
		static SDL_Joystick *joystick = NULL;

		inline void initialise()
		{
			SDL_Init( SDL_INIT_VIDEO | SDL_INIT_JOYSTICK );
			SDL_ShowCursor( 0 );
			SDL_JoystickEventState( SDL_ENABLE );
			SDL_WM_SetIcon( NULL, NULL );
			joystick = SDL_JoystickOpen( 0 );
		}

		inline void cleanup()
		{
			SDL_JoystickClose( joystick );
			SDL_Quit();
		}

		inline void initialiseWindow( const char * name, int w, int h )
		{
			SDL_WM_SetCaption( name, NULL );
			SDL_SetVideoMode( w, h, 24, SDL_OPENGL );
		}

		inline void cleanupWindow()
		{
		}

		inline void endFrame( int fps, unsigned int & savedTime )
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

		inline bool loadImage( std::string const & filePath, ImageData & data )
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

		inline std::string getCurrentDirectory()
		{
			char currentPath[FILENAME_MAX];
			memset( currentPath, 0, sizeof( currentPath ) );
			GetCurrentDir( currentPath, sizeof( currentPath ) );
			std::string current = currentPath;

			if ( current.empty() )
			{
				current = ".";
			}

			current += PATH_SEPARATOR;
			return current;
		}

		inline std::string getDataDirectory()
		{
			return getCurrentDirectory() + "Data";
		}
	}
}

#endif
