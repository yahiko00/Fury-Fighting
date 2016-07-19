#ifndef ___LMP3D_Window_H___
#define ___LMP3D_Window_H___

#include "Common.h"

namespace LMP3D
{
	namespace Windows
	{
		struct Event
		{
			Event();

			int sourisx;
			int sourisy;
			char quit;
			char clikdroit;
			char clikgauche;
			char touche[350];
		};

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
				return event;
			}

		private:
			Event event;
			unsigned int savedTime;
		};
	}
}

#endif
