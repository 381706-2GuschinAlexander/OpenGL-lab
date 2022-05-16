#include <tuple>
#include <cmath>
#include <stdlib.h> 
#include "lib.h"
#include <stdio.h>
#include <gl\glaux.h>
#include <stdexcept>



const GLfloat light_position[] = { .0f, .0f, .0f, 1.0f };
GLuint LoadTexture( const char * filename );
GLuint	textures[2];

static const int FPS = 60;
static GLfloat currentAngleOfRotation = 0.0;

static int slices = 16;
static int stacks = 16;
static void resize(int width, int height)
{
    const float ar = (float)width / (float)height;
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    // gluPerspective(60.0, (GLfloat)width / (GLfloat)height, 1.0, 40.0);
    glFrustum(-ar, ar, -1.0, 1.0, 2.0, 100.0); // Функция glFrustum умножает текущую матрицу
    //на перспективную матрицу.
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

static void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glPushMatrix();
    {
        
        glTranslated(0, 0, -15);
        glRotated(50, 1, 0, 0);
        glLightfv(GL_LIGHT0, GL_POSITION, light_position);
        glPushMatrix();
        {
            
            SetLighting1();
            SetMaterialType1();
            glColor3d(1, 1, 1);
            auto [x, y, z] = get_xyz(currentAngleOfRotation, 7);
            glTranslated(x, y, z);
            glRotated(-currentAngleOfRotation, 0, 1, 0);
            glBindTexture(GL_TEXTURE_2D, textures[1]);
            glEnable(GL_TEXTURE_2D); 
            ConstructSphere(1, slices, stacks);
            glDisable(GL_TEXTURE_2D);
        }
        glPopMatrix();
        
        glPushMatrix();
        {
            SetLighting2();
            SetMaterialType2();
            glColor3d(1, 1, 1);
            glTranslated(0, 0, 0);
            glBindTexture(GL_TEXTURE_2D, textures[0]);
            glEnable(GL_TEXTURE_2D); 
            ConstructSphere(2, slices, stacks);
            glDisable(GL_TEXTURE_2D);
        }
        glPopMatrix();
        
    }
    glPopMatrix();

    glutSwapBuffers();
}

void timer(int v)
{
    if (true)
    {
        currentAngleOfRotation += 1.0;
        if (currentAngleOfRotation > 360.0)
        {
            currentAngleOfRotation -= 360.0;
        }
        glutPostRedisplay();
    }
    glutTimerFunc(1000 / FPS, timer, v);
}

void Initialize()
{
    glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);
    glEnable(GL_LIGHT0);
    glEnable(GL_NORMALIZE);
    glEnable(GL_COLOR_MATERIAL); // для одного или нескольких параметров материала
    glEnable(GL_LIGHTING);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glClearColor(0, 0, 0, 1);
    glGenTextures(2, textures);
    textures[0] = LoadTexture("..//texture/sun.bmp");
    textures[1] = LoadTexture("..//texture/earth.bmp");
    

}



GLuint LoadTexture( const char * filename )
{
  GLuint texture;
  int width, height;
  unsigned char * data;

  FILE * file;
  file = fopen( filename, "rb" );

  if ( file == NULL ) throw std::invalid_argument("No such file");
  width = 256;
  height = 256;
  data = (unsigned char *)malloc( width * height * 3 );
  //int size = fseek(file,);
  fread( data, width * height * 3, 1, file );
  fclose( file );

  for(int i = 0; i < width * height ; ++i)
  {
    int index = i*3;
    unsigned char B,R;
    B = data[index];
    R = data[index+2];

    data[index] = R;
    data[index+2] = B;
  }

  glGenTextures( 1, &texture );
  glBindTexture( GL_TEXTURE_2D, texture );
  glTexEnvf( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE,GL_MODULATE );
  glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_NEAREST );

  glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,GL_LINEAR );
  //glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,GL_REPEAT );
  //glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T,GL_REPEAT );
  gluBuild2DMipmaps( GL_TEXTURE_2D, 3, width, height,GL_RGB, GL_UNSIGNED_BYTE, data );
  free( data );

  return texture;
}

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitWindowSize(1000, 800);
    glutInitWindowPosition(150, 150);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutCreateWindow("GLUT Shapes");
    glutReshapeFunc(resize);
    glutDisplayFunc(display);
    // 9auxDIBImageLoad();
    
    glutTimerFunc(100, timer, 0);
    Initialize();
    glutMainLoop();
    return 0;
}
