#ifndef ___LPM3D_Graphics_Camera_H___
#define ___LPM3D_Graphics_Camera_H___

#include "Movable.h"

namespace LMP3D
{
	namespace Graphics
	{
		/**
		@brief
			Camera management class.
		*/
		class Camera
			: public Movable
		{
		public:
			/**
			@brief
				Constructor.
			*/
			Camera();
			/**
			@brief
				Destructor.
			*/
			~Camera();
			/**
			@brief
				Applies camera's transformations.
			*/
			bool apply()const;
		};
	}
}

#endif
