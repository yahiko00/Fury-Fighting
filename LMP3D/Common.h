#ifndef ___LMP3D_Common_H___
#define ___LMP3D_Common_H___

#include <string>
#include <vector>
#include <cstdio>

namespace LMP3D
{
	typedef unsigned long uint32_t;
	typedef unsigned short uint16_t;
	typedef unsigned char uint8_t;

	typedef long int32_t;
	typedef short int16_t;
	typedef char int8_t;

	typedef std::vector< std::string > StringArray;
	typedef std::vector< uint8_t > ByteArray;

	template< typename T >
	struct pointer
	{
		typedef void( *dtorFunc )( T * );

		inline pointer( T * pointer, dtorFunc dtor )
			: m_pointer( pointer )
			, m_dtor( dtor )
		{
		}

		inline ~pointer()
		{
			( *m_dtor )( m_pointer );
		}

		inline T * operator->()
		{
			return m_pointer;
		}

		inline operator T*()
		{
			return m_pointer;
		}

	private:
		T * m_pointer;
		dtorFunc m_dtor;
	};

	struct Size
	{
		int x;
		int y;

		Size( int x = 0, int y = 0 )
			: x( x )
			, y( y )
		{
		}
	};

	typedef enum PixelFormat
	{
		RGB,
		BGR,
		RGB565,
		BGR565,
		RGBA,
		BGRA,
		ARGB1555,
		ARGB4444,
	}	PixelFormat;

	struct ImageData
	{
		PixelFormat format;
		Size size;
		ByteArray data;
	};

#if !defined( NDEBUG )
#	define logDebug( format, ... ) printf( format, __VA_ARGS__ )
#else
#	define logDebug( format, ... )
#endif
#define	logInfo( format, ... ) printf( format, __VA_ARGS__ )
#define	logError( format, ... ) printf( format, __VA_ARGS__ )
}

#endif
