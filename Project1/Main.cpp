#include <glut.h>
#include <glu.h>

#include "Ball.h"
#include "Box.h"
#include "Commands.h"
#include "Collision.h"
#include "Scenes.h"

using namespace std;


void reshape(int w, int h);
void display();
void init();

GLfloat diffuse0[] = {1.0, 1.0, 1.0, 1.0};

GLfloat light_position[] = {0.0, 0.0, 0.0, 1.0};
GLfloat ambient0[] = {0.1, 0.2, 0.1, 1.0};
GLfloat specular0[] = {0.1, 0.2, 0.1, 1.0};

GLfloat light_emission[] = {1.0, 1.0, 1.0, 1.0};
GLfloat no_emission[] = {0.0, 0.0, 0.0, 1.0};

void display() {

  

  float camera_x = camera_distance * sin(camera_angle);
  float camera_z = camera_distance * cos(camera_angle);

    glLineWidth(2.5); 
    glViewport(0, 0, window_width, window_height);
    // ∏ﬁ¿Œ ∫‰

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, (float)window_width / (float)window_height, 0.1,
                   100.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    gluLookAt(camera_x, 0, -camera_z, 0, 0, 0, 0, 1, 0);

    glEnable(GL_DEPTH_TEST);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambient0);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse0);
    glLightfv(GL_LIGHT0, GL_SPECULAR, specular0);

    GLfloat plane_coef_s[] = {1.0, 0.0, 0.0, 1.0};
    GLfloat plane_coef_t[] = {0.0, 1.0, 0.0, 1.0};
    


    backgroundTexturing();

    glEnable(GL_TEXTURE_2D);
    

    glEnable(GL_TEXTURE_GEN_S);
    glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
    glTexGenfv(GL_S, GL_OBJECT_PLANE, plane_coef_s);

    glEnable(GL_TEXTURE_GEN_T);
    glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
    glTexGenfv(GL_T, GL_OBJECT_PLANE, plane_coef_t);
    
    drawMainScene();
    drawRankings();
    drawHelp();
    if (gameOver) {
      drawGameOverScene();
    }

    int mini_size = min(window_width, window_height) / 3;

    glViewport(window_width - mini_size, 0, mini_size, mini_size);
    // πÃ¥œ∏  ∫‰

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, 1.0, 0.1, 100.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0, 7, 0, 0, 0, 0, 0, 0, 1);

    drawMainScene();

    glViewport(window_width - mini_size, window_height - (mini_size * 2),
               mini_size, mini_size * 2);
    // next ∫‰

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, 0.5, 0.1, 100.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0, 10, 5, 0, 10, 0, 0, 1, 0);

    drawNextFruitScene();

    glViewport(0, window_height - mini_size, mini_size, mini_size);
    // »¶µÂ ∫‰

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, 1.0, 0.1, 100.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0, 20, 2, 0, 20, 0, 0, 1, 0);

    drawHoldScene();
   
  glutSwapBuffers();
}

void reshape(int w, int h) {
  glViewport(0, 0, (GLsizei)w, (GLsizei)h);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(60, (GLfloat)w / (GLfloat)h, 1.0, 100.0);
  glMatrixMode(GL_MODELVIEW);

  window_width = w;
  window_height = h;
}


void init() {
  glClearColor(0.0, 0.0, 0.0, 1.0);
  texturing();
  
  fruits();
  glEnable(GL_DEPTH_TEST);
  glShadeModel(GL_FLAT);
}

int main(int argc, char** argv) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
  glutInitWindowSize(window_width, window_height);
  glutInitWindowPosition(100, 100);

  glutCreateWindow(argv[0]);
  init();

  glutReshapeFunc(reshape);
  
  glutDisplayFunc(display);
  glutIdleFunc(display);


  glutSpecialFunc(special);
  glutKeyboardFunc(keyboard);
  //glutMouseFunc(mouse);
  glutMainLoop();
  return 0;
}
