#ifndef ___LMP3D_Graphics_ObjLoader_H___
#define ___LMP3D_Graphics_ObjLoader_H___

#include <string>

#include "Common.h"

namespace LMP3D
{
	namespace Graphics
	{
		Object LoadObjFile( std::string const & fileName, MaterialMap materials );
	}
}

#endif
