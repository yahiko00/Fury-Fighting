#ifndef ___LMP3D_Graphics_Texture_H___
#define ___LMP3D_Graphics_Texture_H___

#include "Common.h"

namespace LMP3D
{
	namespace Graphics
	{
		class Texture
		{
		public:
			explicit Texture();
			~Texture()throw();

			void setImage( Image const & image );
			bool bind()const;
			void unbind()const;

			inline PixelFormat getFormat()const
			{
				return m_format;
			}

		private:
			PixelFormat m_format;
			unsigned int m_id;
		};
	}
}

#endif
