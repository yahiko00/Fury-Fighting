#ifndef ___LMP3D_Graphics_TexCoordBuffer_H___
#define ___LMP3D_Graphics_TexCoordBuffer_H___

#include "Vector.h"

namespace LMP3D
{
	namespace Graphics
	{
		/**
		@brief
			A buffer holding texture coordinates.
		*/
		class TexCoordBuffer
		{
		public:
			/**
			@brief
				Constructor.
			@param[in] data
				The buffer data.
			*/
			explicit inline TexCoordBuffer( Vector2Array const & data = Vector2Array() )
				: m_data( data )
			{
			}
			/**
			@brief
				Destructor.
			*/
			inline ~TexCoordBuffer()throw()
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
				The coordinates count.
			*/
			inline int getCount()const
			{
				return int( m_data.size() );
			}

		private:
			Vector2Array m_data;
		};
	}
}

#endif
