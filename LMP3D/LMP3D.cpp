#include "LMP3D.h"

#include "Platform.h"
#include "Graphics/Platform.h"

namespace LMP3D
{
	void initialise()
	{
		Platform::initialise();
		Graphics::Platform::initialise();
	}

	void cleanup()
	{
		Graphics::Platform::cleanup();
		Platform::cleanup();
	}
}

