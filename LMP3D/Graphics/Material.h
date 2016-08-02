#ifndef ___LMP3D_Graphics_Material_H___
#define ___LMP3D_Graphics_Material_H___

#include "Texture.h"

namespace LMP3D
{
	namespace Graphics
	{
		/**
		@brief
			Holds a phong material data.
		*/
		class Material
		{
		public:
			/**
			@brief
				Constructor.
			*/
			Material();
			/**
			@brief
				Destructor.
			*/
			~Material()throw();
			/**
			@brief
				Activates the material.
			@return
				\p false if the material was not bound.
			*/
			bool bind()const;
			/**
			@brief
				Deactivates the material.
			*/
			void unbind()const;
			/**
			@brief
				Sets this material's texture.
			@param[in] texture
				The new texture.
			*/
			inline void setTexture( TexturePtr texture )
			{
				m_texture = texture;
			}
			/**
			@brief
				Sets this material's ambient colour.
			@param[in] r,g,b
				The new value.
			*/
			inline void setAmbient( float r, float g, float b )
			{
				m_ambient.r = r;
				m_ambient.g = g;
				m_ambient.b = b;
			}
			/**
			@brief
				Sets this material's ambient colour.
			@param[in] colour
				The new value.
			*/
			inline void setAmbient( Colour3 const & colour )
			{
				setAmbient( colour.g, colour.g, colour.b );
			}
			/**
			@brief
				Sets this material's diffuse colour.
			@param[in] r,g,b
				The new value.
			*/
			inline void setDiffuse( float r, float g, float b )
			{
				m_diffuse.r = r;
				m_diffuse.g = g;
				m_diffuse.b = b;
			}
			/**
			@brief
				Sets this material's diffuse colour.
			@param[in] colour
				The new value.
			*/
			inline void setDiffuse( Colour3 const & colour )
			{
				setDiffuse( colour.g, colour.g, colour.b );
			}
			/**
			@brief
				Sets this material's specular colour.
			@param[in] r,g,b
				The new value.
			*/
			inline void setSpecular( float r, float g, float b )
			{
				m_specular.r = r;
				m_specular.g = g;
				m_specular.b = b;
			}
			/**
			@brief
				Sets this material's specular colour.
			@param[in] colour
				The new value.
			*/
			inline void setSpecular( Colour3 const & colour )
			{
				setSpecular( colour.g, colour.g, colour.b );
			}
			/**
			@brief
				Sets this material's emissive colour.
			@param[in] r,g,b
				The new value.
			*/
			inline void setEmissive( float r, float g, float b )
			{
				m_emissive.r = r;
				m_emissive.g = g;
				m_emissive.b = b;
			}
			/**
			@brief
				Sets this material's emissive colour.
			@param[in] colour
				The new value.
			*/
			inline void setEmissive( Colour3 const & colour )
			{
				setEmissive( colour.g, colour.g, colour.b );
			}
			/**
			@brief
				Sets this material's specular exponent.
			@param[in] exponent
				The new value.
			*/
			inline void setExponent( float exponent )
			{
				m_exponent = exponent;
			}
			/**
			@brief
				Sets this material's opacity.
			@param[in] opacity
				The new value.
			*/
			inline void setOpacity( float opacity )
			{
				m_ambient.a = opacity;
				m_diffuse.a = opacity;
				m_specular.a = opacity;
				m_emissive.a = opacity;
			}
			/**
			@brief
				Tells if this material is opaque.
			@return
				\p true if neither texture nor ambient colour is transparent.
			*/
			inline bool isOpaque()const
			{
				return m_ambient.a >= 1.0 && ( !m_texture || m_texture->getFormat() == RGB || m_texture->getFormat() == BGR );
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
