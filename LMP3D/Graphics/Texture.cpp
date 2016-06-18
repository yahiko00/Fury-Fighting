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
			Platform::DeleteTexture( m_id );
		}

		void Texture::setImage( Image const & image )
		{
			m_format = image.m_format;
			m_id = Platform::CreateTexture();
			Platform::BindTexture( m_id );
			Platform::InitialiseTexture( image.m_size, image.m_format, image.m_data );
			Platform::UnbindTexture();
		}

		bool Texture::bind()const
		{
			if ( m_format == RGBA || m_format == BGRA )
			{
				Platform::EnableBlending();
			}

			return Platform::BindTexture( m_id );
		}

		void Texture::unbind()const
		{
			Platform::UnbindTexture();

			if ( m_format == RGBA || m_format == BGRA )
			{
				Platform::DisableBlending();
			}
		}
	}
}
