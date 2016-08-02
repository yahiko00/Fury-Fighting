#if defined( _arch_dreamcast )

#include "GlutKos.h"

#include <GL/gl.h>
#include <GL/glut.h>
#include <png/kospng.h>
#include <kos.h>

namespace LMP3D
{
	namespace Platform
	{
		void initialise()
		{
			glKosInit();
		}

		void cleanup()
		{
		}

		void initialiseWindow( const char * name, int w, int h )
		{
		}

		void cleanupWindow()
		{
		}

		void endFrame( int fps, unsigned int & savedTime )
		{
			glutSwapBuffers();
		}

		bool loadImage( std::string const & filePath, ImageData & data )
		{
			std::string extension = getFileExtension( filePath );
			extension = lowerCase( extension );
			kos_img_t image = { 0 };

			if ( extension == "png" )
			{
				png_to_img( filePath.c_str(), PNG_FULL_ALPHA, &image );
			}
			else if ( extension == "bmp"
				|| extension == "pcx"
				|| extension == "jpeg")
			{
				//IMG_INFO infos = { IMG_FILE_GUESS, IMG_ALPHA_NONE, 0, IMG_DITHER_NONE, 0, 0, 0 };
				//kos_img_t image = { 0 };
				//img_load_file( filePath.c_str(), &infos, &image );
			}
			else if ( extension == "pvr" )
			{
				//unsigned int color = GL_RGB565_TWID;

				//if ( alpha == 2 )
				//{
				//	color = GL_ARGB4444_TWID;
				//}

				//if ( alpha == 1 )
				//{
				//	color = GL_ARGB1555_TWID;
				//}

				//png_load_texture( filePath.c_str(), &data.kos, alpha, &w, &h );
				//data.m_size = Size( w, h );
			}
			else if ( extension == "tga" )
			{
			}

			if ( image.data )
			{
				data.size = Size( image.w, image.h );
				uint8_t * buffer = static_cast< uint8_t * >( image.data );
				data.data.assign( buffer, buffer + image.byte_count );
				logDebug( "%s\n", "Image infos" );
				logDebug( "  Width %d\n", data.size.x );
				logDebug( "  Height %d\n", data.size.y );
				logDebug( "  Data size %d\n", data.data.size() );

				switch ( image.fmt & KOS_IMG_FMT_MASK )
				{
				case KOS_IMG_FMT_NONE:
					break;
				case KOS_IMG_FMT_RGB888:
					data.format = RGB;
					break;
				case KOS_IMG_FMT_ARGB8888:
					data.format = RGBA;
					break;
				case KOS_IMG_FMT_RGB565:
					data.format = RGB565;
					break;
				case KOS_IMG_FMT_ARGB4444:
					data.format = ARGB4444;
					break;
				case KOS_IMG_FMT_ARGB1555:
					data.format = ARGB1555;
					break;
				case KOS_IMG_FMT_PAL4BPP:
					break;
				case KOS_IMG_FMT_PAL8BPP:
					break;
				case KOS_IMG_FMT_YUV422:
					break;
				case KOS_IMG_FMT_BGR565:
					data.format = BGR565;
					break;
				case KOS_IMG_FMT_RGBA8888:
					data.format = RGBA;
					break;
				}
			}

			return true;
		}

		std::string getCurrentDirectory()
		{
			return "/rd";
		}

		std::string getDataDirectory()
		{
			return getCurrentDirectory();
		}
	}
}

#endif

