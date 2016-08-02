#ifndef ___LMP3D_Graphics_SmdLoader_H___
#define ___LMP3D_Graphics_SmdLoader_H___

#include "GraphicsCommon.h"

namespace LMP3D
{
	namespace Graphics
	{
		/**
		@brief
			Loads an object from a SMD file.
		@param[in] fileName
			The SMD file path
		@param[in,out] scene
			The scene receiving the loaded materials and textures.
		@return
			The loaded object.
		*/
		ObjectPtr loadSmdFile( std::string const & fileName, Scene & scene );
	}
}

#endif
