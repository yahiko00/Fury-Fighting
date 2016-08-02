#ifndef ___LMP3D_SDL_H___
#define ___LMP3D_SDL_H___

#include "../Common.h"

#define LMP3D_INIT_PLATFORM( rom )



namespace LMP3D
{
	namespace Platform
	{
		void initialise();
		void cleanup();
		void initialiseWindow( const char * name, int w, int h );
		void cleanupWindow();
		void endFrame( int fps, unsigned int & savedTime );
		bool loadImage( std::string const & filePath, ImageData & data );
		std::string getCurrentDirectory();
		std::string getDataDirectory();
	}
}

#endif
