#ifndef ___LMP3D_Graphics_Material_H___
#define ___LMP3D_Graphics_Material_H___

#include "Common.h"

namespace LMP3D
{
	namespace Graphics
	{
		class Material
		{
		public:
			Material();
			~Material()throw();

			bool bind()const;
			void unbind()const;

			void setTexture( TexturePtr texture );

			inline void setAmbient( float r, float g, float b )
			{
				m_ambient.r = r;
				m_ambient.g = g;
				m_ambient.b = b;
			}

			inline void setAmbient( Colour3 const & colour )
			{
				setAmbient( colour.g, colour.g, colour.b );
			}

			inline void setDiffuse( float r, float g, float b )
			{
				m_diffuse.r = r;
				m_diffuse.g = g;
				m_diffuse.b = b;
			}

			inline void setDiffuse( Colour3 const & colour )
			{
				setDiffuse( colour.g, colour.g, colour.b );
			}

			inline void setSpecular( float r, float g, float b )
			{
				m_specular.r = r;
				m_specular.g = g;
				m_specular.b = b;
			}

			inline void setSpecular( Colour3 const & colour )
			{
				setSpecular( colour.g, colour.g, colour.b );
			}

			inline void setEmissive( float r, float g, float b )
			{
				m_emissive.r = r;
				m_emissive.g = g;
				m_emissive.b = b;
			}

			inline void setEmissive( Colour3 const & colour )
			{
				setEmissive( colour.g, colour.g, colour.b );
			}

			inline void setExponent( float exponent )
			{
				m_exponent = exponent;
			}

			inline void setOpacity( float opacity )
			{
				m_ambient.a = opacity;
				m_diffuse.a = opacity;
				m_specular.a = opacity;
				m_emissive.a = opacity;
			}

		private:
			Colour4 m_ambient;
			Colour4 m_diffuse;
			Colour4 m_specular;
			Colour4 m_emissive;
			float m_exponent;
			TexturePtr m_texture;
		};
	}
}

#endif
