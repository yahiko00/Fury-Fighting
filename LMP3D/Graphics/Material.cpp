#include "Material.h"

#include "Texture.h"

#include "Platform/OpenGL.h"

namespace LMP3D
{
	namespace Graphics
	{
		Material::Material()
			: m_texture( NULL )
			, m_diffuse( 1.0f, 1.0f, 1.0f, 1.0f )
			, m_exponent( 50.0f )
		{
		}

		Material::~Material()throw()
		{
			delete m_texture;
		}

		bool Material::bind()const
		{
			bool ret = Platform::BindMaterial( m_ambient, m_diffuse, m_specular, m_emissive, m_exponent );

			if ( ret && m_texture )
			{
				ret = m_texture->bind();
			}

			return ret;
		}

		void Material::unbind()const
		{
			if ( m_texture )
			{
				m_texture->unbind();
			}
		}

		void Material::setTexture( TexturePtr texture )
		{
			m_texture = texture;
		}
	}
}
