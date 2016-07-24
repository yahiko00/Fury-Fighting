#ifndef ___LMP3D_Graphics_ObjLoader_H___
#define ___LMP3D_Graphics_ObjLoader_H___

#include "GraphicsCommon.h"

namespace LMP3D
{
	namespace Graphics
	{
		/**
		@brief
			Loads the material file into a scene.
		@param[in] fileName
			The OBJ file path
		@param[in,out] scene
			The scene receiving the loaded materials and textures.
		*/
		void loadMtlFile( std::string const & fileName, Scene & scene );
		/**
		@brief
			Loads an object from an OBJ file.
		@param[in] fileName
			The OBJ file path
		@param[in,out] scene
			The scene receiving the loaded materials and textures.
		@return
			The loaded object.
		*/
		ObjectPtr loadObjFile( std::string const & fileName, Scene & scene );
	}
}

#endif
