#include "Game.h"

using namespace LMP3D;

namespace FuryFighting
{
	namespace
	{
		static int const WINDOW_WIDTH = 640;
		static int const WINDOW_HEIGHT = 480;
	}

	LMP3D_INIT_PLATFORM( romdisk );

	Game::Game( Windows::Window & window )
		: m_window( window )
	{
	}

	Game::~Game()
	{
	}

	void Game::loop()
	{
		Graphics::Viewport viewport( Size( WINDOW_WIDTH, WINDOW_HEIGHT ) );
		Graphics::ObjectPtr object = m_scene.createObject( LMP3D::getDataDirectory() + PATH_SEPARATOR + "Tidus.obj" );

		Graphics::Camera & camera = m_scene.getCamera();
		camera.translate( 0.0f, 1.0f, 5.0f );

		Graphics::Quaternion rotate( Graphics::Vector3( 0, 1, 0 ), Graphics::radians( 10.0f ) );
		Graphics::Quaternion rotate2( Graphics::Vector3( 0, 1, 0 ), Graphics::radians( -10.0f ) );
		size_t count = 0u;
		float angle = 0.0f;
		Graphics::ObjectPtr clone = NULL;
		Position delta;
		Position previous;
		Windows::Event const & event = m_window.getEvent();

		while ( !m_window.getEvent().quit )
		{
			m_window.beginFrame();
			//object->rotate( rotate );
			//object->translate( 0, -0.05f, -0.1f );
			m_window.pollEvent();
			viewport.perspective();
			m_scene.draw();

			Graphics::Vector3 l_up, l_right, l_front;
			camera.getOrientation().toAxes( l_right, l_up, l_front );
			Graphics::Vector3 l_translate;

			camera.rotate( Graphics::radians( event.leftAxisState.y )
						   , Graphics::radians( event.leftAxisState.x )
						   , 0 );

			camera.translate( Graphics::radians( event.rightAxisState.x )
						   , Graphics::radians( event.rightAxisState.y )
						   , 0 );

			if ( event.buttonState[Windows::Button_DPadUp] >= Windows::State_Pressed )
			{
				l_translate += l_front / 5.0f;
			}
			else if ( event.buttonState[Windows::Button_DPadDown] >= Windows::State_Pressed )
			{
				l_translate -= l_front / 5.0f;
			}

			if ( event.buttonState[Windows::Button_DPadRight] >= Windows::State_Pressed )
			{
				l_translate -= l_right / 5.0f;
			}
			else if ( event.buttonState[Windows::Button_DPadLeft] >= Windows::State_Pressed )
			{
				l_translate += l_right / 5.0f;
			}

			camera.translate( l_translate );

			if ( count == 100 )
			{
				//clone = object->clone();
				++count;
			}
			else if ( count < 100 )
			{
				++count;
			}
			else
			{
				//clone->rotate( rotate2 );
				//clone->translate( -0.05f, 0, -0.1f );
			}

			m_window.endFrame( 30 );
			angle += 1;
			angle = fmod( angle, 360.0f );
		}
	}
}
