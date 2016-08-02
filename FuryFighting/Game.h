#include "LMP3D/LMP3D.h"

namespace FuryFighting
{
	class Game
	{
	public:
		Game( LMP3D::Windows::Window & window );
		~Game();

		void loop();

	private:
		LMP3D::Windows::Window & m_window;
		LMP3D::Graphics::Scene m_scene;
	};
}
