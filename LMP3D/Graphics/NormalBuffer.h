#ifndef ___LMP3D_Graphics_NormalBuffer_H___
#define ___LMP3D_Graphics_NormalBuffer_H___

#include "Common.h"

namespace LMP3D
{
	namespace Graphics
	{
		/**
		@brief
			A buffer holding normals.
		*/
		class NormalBuffer
		{
		public:
			/**
			@brief
				Constructor.
			@param[in] data
				The buffer data.
			*/
			explicit inline NormalBuffer( Vector3Array const & data = Vector3Array() )
				: m_data( data )
			{
			}
			/**
			@brief
				Destructor.
			*/
			inline ~NormalBuffer()throw()
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
				The normals count.
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
