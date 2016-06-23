#include "Graphics.h"

#include "Platform/OpenGL.h"

namespace LMP3D
{
	namespace Graphics
	{
		Graphics::Graphics()
		{
			Platform::initialise();
		}

		Graphics::~Graphics()
		{
		}
	}
}
