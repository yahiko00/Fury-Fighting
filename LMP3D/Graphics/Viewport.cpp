#include "Viewport.h"

#include <GL/glew.h>

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
			glViewport( 0, 0, m_size.x, m_size.y );
			glEnable( GL_DEPTH_TEST );
			glMatrixMode( GL_PROJECTION );
			glLoadIdentity();
			gluPerspective( m_angle, m_ratio, m_near, m_far );
			glMatrixMode( GL_MODELVIEW );
		}

		void Viewport::ortho()
		{
			glViewport( 0, 0, m_size.x, m_size.y );
			glDisable( GL_DEPTH_TEST );
			glMatrixMode( GL_PROJECTION );
			glLoadIdentity();
			glOrtho( -1, 1, -1, 1, -1, 1 );
			glMatrixMode( GL_MODELVIEW );
		}
	}
}
