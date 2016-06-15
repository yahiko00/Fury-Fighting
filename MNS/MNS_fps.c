#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "MNS_structure.h"

#if defined( _WIN32 )
#include <Windows.h>

void usleep( __int64 usec )
{
	HANDLE timer;
	LARGE_INTEGER ft;

	ft.QuadPart = -( 10 * usec ); // Convert to 100 nanosecond interval, negative value indicates relative time

	timer = CreateWaitableTimer( NULL, TRUE, NULL );
	SetWaitableTimer( timer, &ft, 0, NULL, NULL, 0 );
	WaitForSingleObject( timer, INFINITE );
	CloseHandle( timer );
}
#endif

void MNS_Fps( MNS_FPS *tim, int fps )
{
	int t = 0, slp;
	slp = 1000000 / fps;

	tim->ta = clock();
	t = tim->ta - tim->tp;

	if ( t <= 0 )
		t = 0;

	if ( t < slp )
		usleep( slp - t );

	tim->tp = clock();
}
