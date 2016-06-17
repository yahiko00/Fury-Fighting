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
			Texture( ByteArray const & data, Size const & size, uint32_t format );
			~Texture()throw();

			bool bind()const;
			void unbind()const;

		protected:
			GLuint m_id;
			Size m_size;
			uint32_t m_format;
			int m_internal;
		};
	}
}

#endif
