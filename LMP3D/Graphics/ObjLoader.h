#pragma once

#include <string>

#include "Common.h"

namespace LMP3D
{
	namespace Graphics
	{
		MeshPtr LoadObjFile( std::string const & fileName );
	}
}
