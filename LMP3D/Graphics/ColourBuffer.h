#ifndef ___LMP3D_Graphics_ColourBuffer_H___
#define ___LMP3D_Graphics_ColourBuffer_H___

#include "GraphicsCommon.h"

namespace LMP3D
{
	namespace Graphics
	{
		/**
		@brief
			A buffer holding colour values.
		*/
		class ColourBuffer
		{
		public:
			/**
			@brief
				Constructor.
			@param[in] data
				The buffer data.
			*/
			explicit inline ColourBuffer( ColourArray const & data = ColourArray() )
				: m_data( data )
			{
			}
			/**
			@brief
				Destructor.
			*/
			inline ~ColourBuffer()throw()
			{
			}
			/**
			@brief
				Activates the buffer.
			@return
				\p false if the buffer was not bound.
			*/
			bool bind()const;
			/**
			@brief
				Deactivates the buffer.
			*/
			void unbind()const;
			/**
			@return
				The colours count.
			*/
			inline int getCount()const
			{
				return int( m_data.size() );
			}

		private:
			ColourArray m_data;
		};
	}
}

#endif
