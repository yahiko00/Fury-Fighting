#ifndef ___LPM3D_Graphics_Viewport_H___
#define ___LPM3D_Graphics_Viewport_H___

#include "GraphicsCommon.h"

namespace LMP3D
{
	namespace Graphics
	{
		/**
		@brief
			Viewport representation, allowing orthographic or perspective projection.
		*/
		class Viewport
		{
		public:
			/**
			@brief
				Constructor.
			@param[in] size
				The viewport dimensions.
			*/
			explicit Viewport( Size const & size );
			/**
			@brief
				Destructor.
			*/
			~Viewport();
			/**
			@brief
				Applies a perspective viewport.
			*/
			void perspective();
			/**
			@brief
				Applies an orthographic viewport.
			*/
			void ortho();
			/**
			@brief
				Updates the viewport dimensions.
			@param[in] x,y
				The new dimensions.
			*/
			void resize( int x, int y );
			/**
			@brief
				Updates the viewport dimensions.
			@param[in] size
				The new dimensions.
			*/
			inline void resize( Size const & size )
			{
				resize( size.x, size.y );
			}

		private:
			Size m_size;
			float m_angle;
			float m_ratio;
			float m_near;
			float m_far;
		};
	}
}

#endif
