#include "Event.h"

#include <cstring>

namespace LMP3D
{
	namespace Windows
	{
		Event::Event()
			: quit( false )
		{
			std::memset( buttonState, 0, sizeof( buttonState ) );
		}
	}
}
