#ifndef ___LPM3D_Graphics_Platform_H___
#define ___LPM3D_Graphics_Platform_H___

#if defined( _WIN32 )
#	include "Platform/OpenGL.h"
#elif defined( _arch_dreamcast )
#	include "Platform/OpenGLKos.h"
#elif defined( _PS2 )
#else
#	include "Platform/OpenGL.h"
#endif

#endif
