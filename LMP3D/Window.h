#ifndef ___LMP3D_Window_H___
#define ___LMP3D_Window_H___

#include "Event.h"

namespace LMP3D
{
	namespace Windows
	{
		class Window
		{
		public:
			Window( const char * name, int w, int h );
			~Window();

			void pollEvent();
			void beginFrame();
			void endFrame( int fps );

			inline Event const & getEvent() const
			{
				return m_event;
			}

		private:
			Event m_event;
			unsigned int m_savedTime;
		};
	}
}

#endif
