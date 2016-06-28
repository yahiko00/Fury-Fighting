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

		void Graphics::initialise()
		{
			doGetSingleton() = new Graphics;
		}

		void Graphics::cleanup()
		{
			delete doGetSingleton();
			doGetSingleton() = NULL;
		}
	}
}
