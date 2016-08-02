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

	/**
	@brief
		RAII wrapper for a pointer.
	*/
	template< typename T >
	struct pointer
	{
		typedef void( *dtorFunc )( T * );

		/**
		@brief
			Constructor.
		@param[in] pointer
			The pointer to be responsible for.
		@param[in] dtor
			The pointer destructor function.
		*/
		inline pointer( T * pointer, dtorFunc dtor )
			: m_pointer( pointer )
			, m_dtor( dtor )
		{
		}
		/**
		@brief
			Destructor, frees the pointer using the dtor given at construction.
		*/
		inline ~pointer()
		{
			( *m_dtor )( m_pointer );
		}
		/**
		@brief
			Pointer member access operator.
		*/
		inline T * operator->()const
		{
			return m_pointer;
		}
		/**
		@brief
			Implicit conversion to pointer type.
		*/
		inline operator T*()const
		{
			return m_pointer;
		}

	private:
		inline pointer( pointer< T > const & )
		{
		}

		inline pointer & operator=( pointer< T > const & )
		{
			return *this;
		}

	private:
		T * m_pointer;
		dtorFunc m_dtor;
	};

	struct Size
	{
		uint16_t x;
		uint16_t y;

		Size( uint16_t x = 0, uint16_t y = 0 )
			: x( x )
			, y( y )
		{
		}
	};

	struct Position
	{
		int16_t x;
		int16_t y;

		Position( int16_t x = 0, int16_t y = 0 )
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
