#ifndef ___LMP3D_Window_H___
#define ___LMP3D_Window_H___

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
			Window();
			~Window();

			void setName( const char *name );
			void setSize( int w, int h );
			void pollEvent();
			void fps( int fps );

			inline Event const & getEvent() const
			{
				return event;
			}

		private:
			Event event;
			unsigned int time_a;
			unsigned int time_b;
		};
	}
}

#endif
