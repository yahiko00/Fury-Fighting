#ifndef ___LMP3D_GLUT_H___
#define ___LMP3D_GLUT_H___

#include "../Common.h"

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#include "LMP3D/FileUtils.h"
#include "LMP3D/StringUtils.h"

#define LMP3D_INIT_PLATFORM( rom )\
	extern uint8_t rom[];\
	KOS_INIT_ROMDISK( rom );

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
