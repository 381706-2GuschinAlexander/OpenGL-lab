#include <tuple>
#include <cmath>
#include <stdlib.h> 
#include "lib.h"
#include <gl\glaux.h>

const GLfloat light_position[] = { .0f, .0f, .0f, 1.0f };

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
        glTranslated(0, 0, -10);
        glRotated(50, 1, 0, 0);
        glLightfv(GL_LIGHT0, GL_POSITION, light_position);
        glPushMatrix();
        {
            SetLighting1();
            SetMaterialType1();
            glColor3d(0, 1, 0);
            auto [x, y, z] = get_xyz(currentAngleOfRotation, 3);
            glTranslated(x, y, z);
            // glRotated(currentAngleOfRotation, 1, 0, 0);
            ConstructSphere(0.7, slices, stacks);
            //glutSolidSphere(0.7, slices, stacks);
        }
        glPopMatrix();

        glPushMatrix();
        {
            SetLighting2();
            SetMaterialType2();
            glColor3d(1, 0.6, 0.21);
            glTranslated(0, 0, 0);
            glutSolidSphere(0.7, slices, stacks);
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
    GLfloat qaLightPosition[] = {0, 0, 1.0, 1.0};
    glLightfv(GL_LIGHT0, GL_POSITION, qaLightPosition);
}

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitWindowSize(1000, 480);
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
