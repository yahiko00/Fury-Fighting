#ifndef ___LMP3D_Graphics_Texture_H___
#define ___LMP3D_Graphics_Texture_H___

#include "GraphicsCommon.h"

namespace LMP3D
{
	namespace Graphics
	{
		class Texture
		{
		public:
			explicit Texture();
			~Texture()throw();

			void load( std::string const fileName );

			bool bind()const;
			void unbind()const;

			PixelFormat getFormat()const;

		private:
			ImageData * m_data;
			TextureId * m_id;
		};
	}
}

#endif
