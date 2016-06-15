
#include <SDL/SDL.h>
#include <GL/glew.h>


typedef struct
{
    int sourisx,sourisy;
    char quit,clikdroit,clikgauche;

    char touche[350];


}LMP3D_event;

namespace LMP3D
{
    class Windows
    {
        public:
            Windows();
            ~Windows();
            void setName(const char *name);
            void setSize(int w,int h);
            void initEvent();
            void getEvent();
            void fps(int fps);

            LMP3D_event event;

        private:
        unsigned int time_a,time_b;
    };

    void Init();
    void Close();
}
