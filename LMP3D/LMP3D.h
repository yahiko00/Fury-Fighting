#ifndef __LMP3D_H___
#define __LMP3D_H___

#include "LMP3D_Window.h"
#include "StringUtils.h"
#include "FileUtils.h"
#include "Graphics/Graphics.h"
#include "Platform.h"

namespace LMP3D
{
	/**
	@brief
		Initialises LMP3D library.
	@remarks
		Initialises platform specifics and Graphics specifics.
	*/
	void initialise();
	/**
	@brief
		Cleans up LMP3D library.
	@remarks
		Cleans up platform specifics and Graphics specifics.
	*/
	void cleanup();
}

#endif
