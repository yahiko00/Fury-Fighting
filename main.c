#include <stdio.h>
#include <stdlib.h>

#include <GL/glew.h>

#include <GL/gl.h>
#include <GL/glu.h>

#include <GL/freeglut.h>

void game();


int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH );//| GLUT_MULTISAMPLE );

    glutInitWindowSize(800,600);
    //glutInitWindowPosition(300,100);
    glutCreateWindow("test");

    glClearColor(0.5,0.5,0.5,0);
    //glClearColor(0,0,0,0);

    //glEnable(GL_CULL_FACE);

    //glPolygonMode (GL_FRONT_AND_BACK, GL_LINE);
    glEnable(GL_TEXTURE_2D);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

    game();

    return 0;
}

char chaine[100];
int fps = 0,T0 = 0;
void test_fps()
{
      fps++;
      if (T0 < glutGet(GLUT_ELAPSED_TIME))
      {
         sprintf(chaine, "Frame rate: %d", fps);
         T0 = glutGet(GLUT_ELAPSED_TIME) +1000;
         fps = 0;
      }

      MNS_Camera_Ortho();
      glLoadIdentity();
      glRasterPos2i(-1,-1);


      glDisable(GL_TEXTURE_2D);
      glColor4f(0,0,0,0);

      glutBitmapString(GLUT_BITMAP_TIMES_ROMAN_24, chaine);

      glColor4f(1,1,1,1);
      glEnable(GL_TEXTURE_2D);
}

