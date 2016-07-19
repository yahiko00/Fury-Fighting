#ifndef ___LMP3D_Graphics_ObjLoader_H___
#define ___LMP3D_Graphics_ObjLoader_H___

#include "GraphicsCommon.h"

namespace LMP3D
{
	namespace Graphics
	{
		void loadMtlFile( std::string const & fileName, Scene & scene );
		ObjectPtr loadObjFile( std::string const & fileName, Scene & scene );
	}
}

#endif
