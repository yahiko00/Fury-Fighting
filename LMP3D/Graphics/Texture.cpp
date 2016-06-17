#include "Texture.h"

#include <GL/glew.h>

#include <cassert>

namespace LMP3D
{
	namespace Graphics
	{
		namespace
		{
			int GetInternal( uint32_t format )
			{
				switch ( format )
				{
				case GL_RGB:
				case GL_BGR:
					return 3;

				case GL_RGBA:
				case GL_BGRA:
					return 4;

				default:
					assert( false && "Unexpected texture format" );
					return 3;
				}
			}
		}

		Texture::Texture( ByteArray const & data, Size const & size, uint32_t format )
			: m_size( size )
			, m_format( format )
			, m_internal( GetInternal( format ) )
		{
			glGenTextures( 1, &m_id );
			glBindTexture( GL_TEXTURE_2D, m_id );
			glTexImage2D( GL_TEXTURE_2D, 0, m_internal, m_size.x, m_size.y, 0, m_format, GL_UNSIGNED_BYTE, &data[0] );
			glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
			glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
			glBindTexture( GL_TEXTURE_2D, 0 );
		}

		Texture::~Texture()throw()
		{
			glDeleteTextures( 1, &m_id );
		}

		bool Texture::bind()const
		{
			glBindTexture( GL_TEXTURE_2D, m_id );
			return checkGlError( "glBindTexture" );
		}

		void Texture::unbind()const
		{
			glBindTexture( GL_TEXTURE_2D, 0 );
		}
	}
}
