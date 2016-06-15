#ifndef ___LMP3D_Window___
#define ___LMP3D_Window___

namespace LMP3D
{
	namespace Windows
	{
		struct Event
		{
			int sourisx{ 0 };
			int sourisy{ 0 };
			char quit{ 0 };
			char clikdroit{ 0 };
			char clikgauche{ 0 };
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
			unsigned int time_a{ 0 };
			unsigned int time_b{ 0 };
		};
	}
}

#endif
