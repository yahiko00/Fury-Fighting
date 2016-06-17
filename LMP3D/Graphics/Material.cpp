#include "Material.h"

#include "Texture.h"

#include <GL/glew.h>

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
			glMaterialfv( GL_FRONT, GL_AMBIENT, &m_ambient.r );
			glMaterialfv( GL_FRONT, GL_AMBIENT, &m_diffuse.r );
			glMaterialfv( GL_FRONT, GL_AMBIENT, &m_specular.r );
			glMaterialfv( GL_FRONT, GL_AMBIENT, &m_emissive.r );
			glMaterialf( GL_FRONT, GL_SHININESS, m_exponent );
			bool ret = checkGlError( "glMaterial" );

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
