#include "Texture.h"

#include "Platform.h"

namespace LMP3D
{
	namespace Graphics
	{
		Texture::Texture()
		{
		}

		Texture::~Texture()throw()
		{
			Platform::deleteTexture( m_id );
		}

		void Texture::setImage( Image const & image )
		{
			m_format = image.m_format;
			m_id = Platform::createTexture();
			Platform::bindTexture( m_id );
			Platform::initialiseTexture( image.m_size, image.m_format, image.m_data );
			Platform::unbindTexture();
		}

		bool Texture::bind()const
		{
			if ( m_format == RGBA || m_format == BGRA )
			{
				Platform::enableBlending();
			}

			return Platform::bindTexture( m_id );
		}

		void Texture::unbind()const
		{
			Platform::unbindTexture();

			if ( m_format == RGBA || m_format == BGRA )
			{
				Platform::disableBlending();
			}
		}
	}
}
