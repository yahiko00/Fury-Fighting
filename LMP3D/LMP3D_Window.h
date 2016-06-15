

#ifndef _LMP3D_Window__
#define _LMP3D_Window__

#include "LMP3D.h"

typedef struct
{
    int sourisx,sourisy;
    char quit,clikdroit,clikgauche;

    char touche[350];


}LMP3D_event;

namespace LMP3D
{
    namespace Window
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

                LMP3D_event event;

            private:
                unsigned int time_a,time_b;
        };
    }

}


#endif
