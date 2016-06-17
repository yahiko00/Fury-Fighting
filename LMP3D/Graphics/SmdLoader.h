#ifndef ___LMP3D_Graphics_SmdLoader_H___
#define ___LMP3D_Graphics_SmdLoader_H___

#include <string>

#include "Common.h"

namespace LMP3D
{
	namespace Graphics
	{
		MeshPtr LoadSmdMesh( std::string const & fileName );
	}
}

#endif
