#ifndef ___LMP3D_Graphics_Texture_H___
#define ___LMP3D_Graphics_Texture_H___

#include "GraphicsCommon.h"

namespace LMP3D
{
	namespace Graphics
	{
		/**
		@brief
			A texture, with an image and platform specifics.
		*/
		class Texture
		{
		public:
			/**
			@brief
				Constructor.
			*/
			explicit Texture();
			/**
			@brief
				Destructor.
			*/
			~Texture()throw();
			/**
			@brief
				Loads the texture image and initialises platform specifics.
			@param[in]
				The image file name.
			*/
			void load( std::string const fileName );
			/**
			@brief
				Activates the texture.
			@return
				\p false if the texture was not bound.
			*/
			bool bind()const;
			/**
			@brief
				Deactivates the texture.
			*/
			void unbind()const;
			/**
			@return
				The image pixel format.
			*/
			PixelFormat getFormat()const;

		private:
			ImageData * m_data;
			TextureId * m_id;
		};
	}
}

#endif
