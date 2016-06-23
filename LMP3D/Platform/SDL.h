#ifndef ___LMP3D_SDL_H___
#define ___LMP3D_SDL_H___

#include "LMP3D/Common.h"

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <cstdio>  /* defines FILENAME_MAX */
#include <cstring>

#include "StringUtils.h"

#ifdef _WIN32
#	include <direct.h>
#	define GetCurrentDir _getcwd
#else
#	include <unistd.h>
#	define GetCurrentDir getcwd
#endif

namespace LMP3D
{
	namespace Platform
	{
		inline Image loadImage( std::string const & filePath )
		{
			pointer< SDL_Surface > image( IMG_Load( filePath.c_str() ), SDL_FreeSurface );
			Image ret;

			if ( image )
			{
				if ( image->format->BytesPerPixel == 3 )
				{
					if ( image->format->Rmask > image->format->Gmask )
					{
						ret.m_format = BGR;
					}
					else
					{
						ret.m_format = RGB;
					}
				}
				else if ( image->format->BytesPerPixel == 4 )
				{
					if ( image->format->Amask > image->format->Rmask )
					{
						ret.m_format = BGRA;
					}
					else
					{
						ret.m_format = RGBA;
					}
				}

				uint8_t * data = reinterpret_cast< uint8_t * >( image->pixels );
				ret.m_size = Size( image->w, image->h );
				ret.m_data.insert( ret.m_data.end(), data, data + image->pitch * image->h );
			}

			return ret;
		}
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
}

#endif
