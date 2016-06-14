#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <SDL/SDL.h>
#include <GL/gl.h>

#include "MNS/MNS.h"

#ifdef __MINGW32__
#undef main
#endif


void game();

int main(void)
{
    SDL_Joystick *joystick = NULL;
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_JOYSTICK);

    srand(time(NULL));

    SDL_ShowCursor(0);
    SDL_JoystickEventState(SDL_ENABLE);
    joystick = SDL_JoystickOpen(0);

    SDL_WM_SetIcon(  NULL  , NULL);
    SDL_WM_SetCaption("Fury Fighting", NULL);

    SDL_SetVideoMode(640,480, 24,SDL_OPENGL);

    glClearColor(0.5,0.5,0.5,0);

    //glEnable(GL_CULL_FACE);

    glEnable(GL_TEXTURE_2D);
    glAlphaFunc(GL_GREATER, 0.0f);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    game();

    SDL_JoystickClose(joystick);
    SDL_Quit();

    return 0;
}

void game()
{
    //while(1)
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);





		glFlush();
		SDL_GL_SwapBuffers();


		SDL_Delay(1000);

    }
}

