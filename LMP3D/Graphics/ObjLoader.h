#ifndef ___LMP3D_Graphics_ObjLoader_H___
#define ___LMP3D_Graphics_ObjLoader_H___

#include "Common.h"

namespace LMP3D
{
	namespace Graphics
	{
		void loadMtlFile( std::string const & fileName );
		ObjectPtr loadObjFile( std::string const & fileName );
	}
}

#endif
