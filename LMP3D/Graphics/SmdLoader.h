#ifndef ___LMP3D_Graphics_SmdLoader_H___
#define ___LMP3D_Graphics_SmdLoader_H___

#include "GraphicsCommon.h"

namespace LMP3D
{
	namespace Graphics
	{
		ObjectPtr loadSmdFile( std::string const & fileName, Scene & scene );
	}
}

#endif
