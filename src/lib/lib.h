#include <GL/glut.h>
#include <tuple>
#include <cmath>

void SetMaterialType1(){
  const GLfloat mat_ambient[] = { 0.7f, 0.7f, 0.7f, 1.0f }; 
  const GLfloat mat_diffuse[] = { 0.8f, 0.8f, 0.8f, 1.0f }; 
  const GLfloat mat_specular[] = { .0f, .0f, .0f, 1.0f }; 
  const GLfloat high_shininess[] = { 100.0f }; 

  glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
  glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
  glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
  glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);
}

void SetMaterialType2(){
  const GLfloat mat_ambient[] = { 1.f, 1.f, 1.f, 1.0f }; 
  const GLfloat mat_diffuse[] = { .0f, .0f, .0f, 1.0f }; 
  const GLfloat mat_specular[] = { .0f, .0f, .0f, 1.0f }; 
  const GLfloat high_shininess[] = { 100.0f }; 

  glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
  glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
  glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
  glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);
}

void SetLighting1(){
  const GLfloat light_ambient[] = {0.1f, 0.1f, 0.1f, 1.0f};
  const GLfloat light_diffuse[] = {0.8f, 0.8f, 0.8f, 1.0f};
  const GLfloat light_specular[] = {0.5f, 0.5f, 0.5f, 1.0f};

  glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
  glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
  glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
}

void SetLighting2(){
  const GLfloat light_ambient[] = {1.f, 1.f, 1.f, 1.0f};
  const GLfloat light_diffuse[] = {.0f, .0f, .0f, 1.0f};
  const GLfloat light_specular[] = {.0f, .0f, .0f, 1.0f};

  glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
  glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
  glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
}

std::tuple<double, double, double> get_xyz(double angle, double r){
  double rad = angle * M_PI / 180; 
  return std::make_tuple(r * cos(rad), 0, r * sin(rad));
}

void ConstructSphere(double r, int x_slices, int y_slices){
    auto find_xyz = [=](double teta, double phi)->std::tuple<float, float, float>{
        return std::make_tuple(r * sin(teta) * cos(phi), r*cos(teta), r * sin(teta) * sin(phi));
    };
    auto radian = [](double angle){
        return angle * M_PI / 180;
    };

 
    double x_step = 360.0 / x_slices, y_step = 180.0 / y_slices;
    double phi_step  = radian(x_step), teta_step  = radian(y_step);
    float fx = 1.0f/x_slices, fy = 1.0f/x_slices;

    glBegin(GL_QUADS);
    for(int  i = 0; i < y_slices; ++i){
        double cur_teta = teta_step * i;
        for(int j = 0; j < x_slices; ++j){
            double cur_phi = phi_step * j;

            auto [x00, y00, z00] = find_xyz(cur_teta + teta_step, cur_phi);
            auto [x01, y01, z01] = find_xyz(cur_teta, cur_phi);
            auto [x10, y10, z10] = find_xyz(cur_teta + teta_step, cur_phi + phi_step);
            auto [x11, y11, z11] = find_xyz(cur_teta, cur_phi + phi_step);

            // glTexCoord2f(1.0f , 0.0f); glNormal3f(x10, y10, z10); glVertex3f(x10, y10, z10);
            // glTexCoord2f(1.0f, 1.0f); glNormal3f(x00, y00, z00); glVertex3f(x00, y00, z00);//right
            // glTexCoord2f(0.0f, 1.0f); glNormal3f(x01, y01, z01); glVertex3f(x01, y01, z01);
            // glTexCoord2f(0.0f, 0.0f); glNormal3f(x11, y11, z11); glVertex3f(x11, y11, z11);

            glTexCoord2f(1.f - fx * j, 1.f - fy * (i + 1)); glNormal3f(x00, y00, z00); glVertex3f(x00, y00, z00);
            glTexCoord2f(1.f - fx * j, 1.f - fy * i); glNormal3f(x01, y01, z01); glVertex3f(x01, y01, z01);
            glTexCoord2f(1.f - fx * (j + 1), 1.f - fy * i); glNormal3f(x11, y11, z11); glVertex3f(x11, y11, z11);
            glTexCoord2f(1.f - fx * (j + 1), 1.f - fy * (i + 1)); glNormal3f(x10, y10, z10); glVertex3f(x10, y10, z10);
        }
    }
    glEnd();
}