#include <tuple>
#include <cmath>
#include <stdlib.h> 
#include "lib.h"
#include <stdio.h>
#include <stdexcept>



const GLfloat light_position[] = { .0f, .0f, .0f, 1.0f };
GLuint LoadTexture( const char * filename );
const int texture_size = 3;
GLuint	textures[texture_size];

static const int FPS = 60;
static GLfloat inc         = 5.0;
static GLfloat earth_angle = 0.0;
static GLfloat orbit_angle = 0.0;
static GLfloat moon_angle = 0.0;
static GLfloat sun_angle = 0.0;
static double  zoom = - 20;

static int slices = 16;
static int stacks = 16;
static void resize(int width, int height)
{
    const float ar = (float)width / (float)height;
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-ar, ar, -1.0, 1.0, 2.0, 100.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

static void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glPushMatrix();
    {  
        glTranslated(0, 0, zoom);
        glRotated(20, 1, 0, 0);
        glLightfv(GL_LIGHT0, GL_POSITION, light_position);
        glPushMatrix();
        {
            
            SetLighting1();
            SetMaterialType1();
            glColor3d(1, 1, 1);
            auto [x, y, z] = get_xyz(-orbit_angle, 9);
            glTranslated(x, y, z);
            glRotated(-23.5, 0, 0, 1);

             glPushMatrix();
            {
                auto [x1, y1, z1] = get_xyz(-moon_angle, 2);
                glTranslated(x1, y1, z1);
                glRotated(-moon_angle, 0, 1, 0);
                glBindTexture(GL_TEXTURE_2D, textures[2]);
                glEnable(GL_TEXTURE_2D);
                ConstructSphere(0.3, slices, stacks);
                glDisable(GL_TEXTURE_2D);
            }
            glPopMatrix();


            glRotated(-earth_angle, 0, 1, 0);
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
            glRotated(sun_angle, 0, 1, 0);
            ConstructSphere(2, 24, 24);
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
        earth_angle += inc;
        orbit_angle += inc / 10.0;
        moon_angle  += inc / 5.0;
        sun_angle += inc / 30.0;
        if (earth_angle > 360.0)
        {
            earth_angle -= 360.0;
        }
        if (sun_angle > 360.0)
        {
            sun_angle -= 360.0;
        }
        if(orbit_angle > 360)
        {
            orbit_angle -= 360.0;
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
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHTING);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glClearColor(0, 0, 0, 1);
    glGenTextures(texture_size, textures);
    textures[0] = LoadTexture("../texture/sun.bmp");
    textures[1] = LoadTexture("../texture/earth.bmp");
    textures[2] = LoadTexture("../texture/moon.bmp");
}



GLuint LoadTexture( const char * filename )
{
  GLuint texture;
  int width, height;
  unsigned char * data;

  FILE * file;
  file = fopen( filename, "rb" );

  if ( file == NULL ) throw std::invalid_argument("No such file");
  width = 1024;
  height = 512;
  data = (unsigned char *)malloc( width * height * 3 );
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
  glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,GL_REPEAT );
  glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T,GL_REPEAT );
  gluBuild2DMipmaps( GL_TEXTURE_2D, 3, width, height,GL_RGB, GL_UNSIGNED_BYTE, data );
  free( data );

  return texture;
}


void keys(int key, int x, int y) { 
    switch (key)
    {
    case GLUT_KEY_RIGHT:
        inc  += 0.25; 
        break;
    case GLUT_KEY_LEFT:
        inc  -= 0.25; 
        break;
    case GLUT_KEY_UP:
        zoom  += 0.25;
        break;
    case GLUT_KEY_DOWN:
        zoom  -= 0.25;
        break;
    
    default:
        break;
    }
} 


int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitWindowSize(1980, 1240);
    glutInitWindowPosition(150, 150);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutCreateWindow("GLUT Shapes");
    glutReshapeFunc(resize);
    glutDisplayFunc(display);
    glutSpecialFunc(keys);
    glutTimerFunc(100, timer, 0);
    Initialize();
    glutMainLoop();
    return 0;
}
