#ifndef ___LPM3D_Platform_H___
#define ___LPM3D_Platform_H___

#if defined( _WIN32 )
#	include "Platform/SDL.h"
#elif defined( _arch_dreamcast )
#	include "Platform/GlutKos.h"
#elif defined( _PS2 )
#else
#	include "Platform/SDL.h"
#endif

#endif
