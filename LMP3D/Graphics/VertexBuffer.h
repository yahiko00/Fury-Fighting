#ifndef ___LMP3D_Graphics_VertexBuffer_H___
#define ___LMP3D_Graphics_VertexBuffer_H___

#include "Vector.h"

namespace LMP3D
{
	namespace Graphics
	{
		/**
		@brief
			A buffer holding vertex positions.
		*/
		class VertexBuffer
		{
		public:
			/**
			@brief
				Constructor.
			@param[in] data
				The buffer data.
			*/
			explicit inline VertexBuffer( Vector3Array const & data = Vector3Array() )
				: m_data( data )
			{
			}
			/**
			@brief
				Destructor.
			*/
			inline ~VertexBuffer()throw()
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
				The positions count.
			*/
			inline int getCount()const
			{
				return int( m_data.size() );
			}

		private:
			Vector3Array m_data;
		};
	}
}

#endif
