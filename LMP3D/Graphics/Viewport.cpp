#include "Viewport.h"

#include "Platform/OpenGL.h"

namespace LMP3D
{
	namespace Graphics
	{
		Viewport::Viewport( Size const & size )
			: m_angle( 72.0f )
			, m_ratio( float( size.x ) / size.y )
			, m_size( size )
			, m_near( 0.1f )
			, m_far( 1000.0f )
		{
		}

		Viewport::~Viewport()
		{
		}

		void Viewport::resize( int x, int y )
		{
			m_size.x = x;
			m_size.y = y;
			m_ratio = float( x ) / y;
		}

		void Viewport::perspective()
		{
			Platform::Viewport( m_size );
			Platform::Perspective( m_angle, m_ratio, m_near, m_far );
		}

		void Viewport::ortho()
		{
			Platform::Viewport( m_size );
			Platform::Ortho( -1, 1, -1, 1, -1, 1 );
		}
	}
}
