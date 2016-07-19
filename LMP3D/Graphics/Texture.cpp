#include "Texture.h"

#include "Platform.h"
#include "../Platform.h"

namespace LMP3D
{
	namespace Graphics
	{
		Texture::Texture()
		{
		}

		Texture::~Texture()throw()
		{
			Platform::deleteTexture( m_id, m_data );
		}

		void Texture::load( std::string const fileName )
		{
			Platform::createTexture( m_id, m_data );
			LMP3D::Platform::loadImage( fileName, *m_data );
			Platform::bindTexture( *m_id );
			Platform::initialiseTexture( *m_id, *m_data );
			Platform::unbindTexture();
		}

		bool Texture::bind()const
		{
			if ( m_data->format == RGBA || m_data->format == BGRA )
			{
				Platform::enableBlending();
			}

			return Platform::bindTexture( *m_id );
		}

		void Texture::unbind()const
		{
			Platform::unbindTexture();

			if ( m_data->format == RGBA || m_data->format == BGRA )
			{
				Platform::disableBlending();
			}
		}

		PixelFormat Texture::getFormat()const
		{
			return m_data->format;
		}
	}
}
