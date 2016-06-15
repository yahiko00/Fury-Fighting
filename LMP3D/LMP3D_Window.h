

#ifndef _LMP3D_Window__
#define _LMP3D_Window__

#include "LMP3D.h"

typedef struct
{
    int sourisx,sourisy;
    char quit,clikdroit,clikgauche;

    char touche[350];


}Event;

namespace LMP3D
{
    namespace Windows
    {
        class Window
        {
            public:
                Window();
                ~Window();
                void setName(const char *name);
                void setSize(int w,int h);
                void initEvent();
                void getEvent();
                void fps(int fps);

                Event event;

            private:
                unsigned int time_a,time_b;
        };
    }

}


#endif
