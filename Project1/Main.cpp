#include <glut.h>
#define _USE_MATH_DEFINES

#include <cmath>
#include <vector>
#include <random>
#include <cmath>


using namespace std;

std::default_random_engine generator;
std::uniform_real_distribution<float> radiusDistribution(0.1f, 0.5f);

struct Ball {
  float x, y, z;
  float vx, vy, vz;  // x, y, z 각각의 속도
  float mass;
  float radius;

  Ball() {
    radius = radiusDistribution(generator);

  }
};

void keyboard(unsigned char keyPressed, int x, int y);
bool areColliding(const Ball& a, const Ball& b);
void handleCollision(Ball& a, Ball& b);
void drawWireBoxWithoutTop();
void reshape(int w, int h);
void display(void);
//void mouse(int button, int state, int x, int y);
void special(int key, int x, int y);
void drawScene();

int camera_x = 0;
int camera_y = 0;
int camera_z = 7;

float camera_distance = 7.0f;  // 카메라와 상자 사이의 거리
float camera_angle = 0.0f;     // 카메라 각도
float min_distance = 6.0f; //카메라와 상자의 최소 거리
float max_distance = 13.0f;     // 카메라와 상자의 최소 거리

float marker_x = 0.0f, marker_y = 2.5f, marker_z = 0.0f;

int window_width = 1920;  
int window_height = 1080;   

std::vector<Ball> balls;

void display(void) {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  float camera_x = camera_distance * sin(camera_angle);
  float camera_z = camera_distance * cos(camera_angle);

  glViewport(0, 0, window_width, window_height);
  // 메인 뷰

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(60.0, (float)window_width / (float)window_height, 0.1, 100.0);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  gluLookAt(camera_x, camera_y, camera_z, 0, 0, 0, 0, 1, 0);  

  drawScene();

  int mini_size = min(window_width, window_height) / 4;

  glViewport(window_width - mini_size, 0, mini_size, mini_size);
  // 미니 뷰

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(60.0, 1.0, 0.1, 100.0);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  gluLookAt(0, 7, 0, 0, 0, 0, 0, 0, 1);
  

  drawScene();

  glutSwapBuffers();
}

/*
//////////////////////////////////////////////////////////////////////////////////////////




       draw Scene




////////////////////////////////////////////////////////////////////////////////////////////
*/


void drawScene() {
  glPushMatrix();
  glScalef(2.0, 2.0, 2.0);
  drawWireBoxWithoutTop();
  glPopMatrix();

  for (auto& ball : balls) {
    glPushMatrix();
    glTranslatef(ball.x, ball.y, ball.z);
    glutSolidSphere(ball.radius, 100, 100);
    glPopMatrix();

    ball.x += ball.vx;  // 속도에 따른 공의 위치 변경
    ball.y += ball.vy;
    ball.z += ball.vz;

    ball.vy -= 0.001;  // gravity

    // 벽과 공의 충돌
    if (ball.x - ball.radius < -2) {
      ball.vx = -0.1f * ball.vx;  // 상수값이 변경됨에 따라 충돌 세기가 변경됨
      ball.x = -2 + ball.radius;  
    } else if (ball.x + ball.radius > 2) {
      ball.vx = -0.1f * ball.vx;  
      ball.x = 2 - ball.radius;   
    }

    if (ball.y - ball.radius < -2) {
      ball.vy = -0.1f * ball.vy;  
      ball.y = -2 + ball.radius;  
    }

    if (ball.z - ball.radius < -2) {
      ball.vz = -0.1f * ball.vz; 
      ball.z = -2 + ball.radius;  
    } else if (ball.z + ball.radius > 2) {
      ball.vz = -0.1f * ball.vz;  
      ball.z = 2 - ball.radius;   
    }

    // 공과 공사이의 충돌 검사
    for (auto& other : balls) {
      if (&ball != &other && areColliding(ball, other)) {
        handleCollision(ball, other);
      }
    }
  }
  glColor3f(1.0f, 0.0f, 0.0f);  // 빨간색
  glPushMatrix();
  glTranslatef(marker_x, marker_y, marker_z);
  glutSolidSphere(0.1, 20, 20);  // 여기에 앞으로 떨굴 공을 표시
  glPopMatrix();

  glColor3f(1.0f, 0.0f, 0.0f); 
  glBegin(GL_LINES);
  glVertex3f(marker_x, -2.0f, marker_z);  // 박스 바닥부터 천장까지 이어줌
  glVertex3f(marker_x, 2.5f, marker_z);   
  glEnd();

  glColor3f(1.0f, 1.0f, 1.0f);  // 다시 흰색으로 복구

  
}





/*
//////////////////////////////////////////////////////////////////////////////////////////




       input, commands, camera controll




////////////////////////////////////////////////////////////////////////////////////////////
*/

// 클릭으로 공 생성 (미사용)
/*
void mouse(int button, int state, int x, int y) {
  if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
    double modelview[16], projection[16];
    int viewport[4];
    double d_x, d_y, d_z;


    glGetDoublev(GL_MODELVIEW_MATRIX, modelview);
    glGetDoublev(GL_PROJECTION_MATRIX, projection);
    glGetIntegerv(GL_VIEWPORT, viewport);


    double win_x = (double)x;
    double win_y = (double)viewport[3] - (double)y;


    gluUnProject(win_x, win_y, 0.0, modelview, projection, viewport, &d_x, &d_y,
                 &d_z);

    Ball ball;
    ball.x = d_x;
    ball.y = d_y;
    ball.z = d_z;
    ball.vx = ball.vy = ball.vz = 0;
    ball.mass = 1.0f;
    ball.radius = 0.1;
    balls.push_back(ball);
  }
}
*/

void keyboard(unsigned char keyPressed, int x, int y) {
  switch (keyPressed) {
    case 'w':
      if (camera_distance >
          min_distance) {  // 카메라가 상자에 너무 가깝지 않은 경우에만 이동
        camera_distance -= 1.0f;  // 카메라를 상자에 가깝게 이동
      }
      break;
    case 's':
      if (camera_distance < max_distance) { // 동일
        camera_distance += 1.0f;  // 카메라를 상자에서 멀어지게 이동
      }
      break;
    case 'a':
      camera_angle -= M_PI / 180.0f;  // 카메라를 왼쪽으로 회전
      break;
    case 'd':
      camera_angle += M_PI / 180.0f;  // 카메라를 오른쪽으로 회전
      break;
    case ' ':                       // 엔터 입력시 공 생성
      Ball ball;
      ball.x = marker_x;
      ball.y = marker_y;
      ball.z = marker_z;
      ball.vx = ball.vy = ball.vz = 0;
      ball.mass = 1.0f;             // 질량은 반지름에 따라 달라야 할까?
      balls.push_back(ball);
      break;
  }
  glutPostRedisplay();
}


void special(int key, int x, int y) {   // 화살표키 조종
  switch (key) {
    case GLUT_KEY_LEFT:
      marker_x += 0.1f;
      break;
    case GLUT_KEY_RIGHT:
      marker_x -= 0.1f;
      break;
    case GLUT_KEY_UP:
      marker_z += 0.1f;
      break;
    case GLUT_KEY_DOWN:
      marker_z -= 0.1f;
      break;
  }

  // 표시가 박스를 벗어나지 않도록 최대, 최소값 설정

  marker_x = std::max(-2.0f, std::min(2.0f, marker_x));

  marker_z = std::max(-2.0f, std::min(2.0f, marker_z));

  glutPostRedisplay();
}


















/*
//////////////////////////////////////////////////////////////////////////////////////////




        handle Coliisions




////////////////////////////////////////////////////////////////////////////////////////////
*/


// 공이 서로 충돌중인지 확인
bool areColliding(const Ball& a, const Ball& b) {
  float dx = a.x - b.x;
  float dy = a.y - b.y;
  float dz = a.z - b.z;
  float distance = std::sqrt(dx * dx + dy * dy + dz * dz);
  return distance < a.radius + b.radius;  
}


void handleCollision(Ball& a, Ball& b) {
  // normal vector 계산
  float nx = a.x - b.x;
  float ny = a.y - b.y;
  float nz = a.z - b.z;
  float n_length = std::sqrt(nx * nx + ny * ny + nz * nz);
  nx /= n_length;
  ny /= n_length;
  nz /= n_length;

  // 상대 속도 계산
  float rvx = a.vx - b.vx;
  float rvy = a.vy - b.vy;
  float rvz = a.vz - b.vz;

  // 탄성 충돌 반응
  float e = 0.1f;  // 반발계수, 높아지면 더 세게 튕겨짐
  float j = -(1.0f + e) * (rvx * nx + rvy * ny + rvz * nz) /
            (1.0f / a.mass + 1.0f / b.mass);

  // 충돌에 따른 속도의 변화
  a.vx += j * nx / a.mass;
  a.vy += j * ny / a.mass;
  a.vz += j * nz / a.mass;
  b.vx -= j * nx / b.mass;
  b.vy -= j * ny / b.mass;
  b.vz -= j * nz / b.mass;

  // 공들의 위치를 수정하여 겹치지 않도록 함
  float overlap = a.radius + b.radius - n_length;  // 공들의 반지름 합을 n_length와 비교
  if (overlap > 0) {
    a.x += overlap / 2 * nx;
    a.y += overlap / 2 * ny;
    a.z += overlap / 2 * nz;
    b.x -= overlap / 2 * nx;
    b.y -= overlap / 2 * ny;
    b.z -= overlap / 2 * nz;
  }
}








/*
//////////////////////////////////////////////////////////////////////////////////////////




        reshape, main, init




////////////////////////////////////////////////////////////////////////////////////////////
*/
void reshape(int w, int h) {
  glViewport(0, 0, (GLsizei)w, (GLsizei)h);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(60, (GLfloat)w / (GLfloat)h, 1.0, 100.0);
  glMatrixMode(GL_MODELVIEW);

  window_width = w;
  window_height = h;
}


void init(void) {
  glClearColor(0.0, 0.0, 0.0, 0.0);
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


/*
//////////////////////////////////////////////////////////////////////////////////////////




        drawBox




////////////////////////////////////////////////////////////////////////////////////////////
*/
void drawWireBoxWithoutTop() {
  glBegin(GL_LINES);

  // Bottom
  glVertex3f(-1.0, -1.0, -1.0);
  glVertex3f(1.0, -1.0, -1.0);

  glVertex3f(1.0, -1.0, -1.0);
  glVertex3f(1.0, 1.0, -1.0);

  // glVertex3f(1.0, 1.0, -1.0);
  // glVertex3f(-1.0, 1.0, -1.0);

  glVertex3f(-1.0, 1.0, -1.0);
  glVertex3f(-1.0, -1.0, -1.0);

  // Top
  glVertex3f(-1.0, -1.0, 1.0);
  glVertex3f(1.0, -1.0, 1.0);

  glVertex3f(1.0, -1.0, 1.0);
  glVertex3f(1.0, 1.0, 1.0);

  // glVertex3f(1.0, 1.0, 1.0);
  // glVertex3f(-1.0, 1.0, 1.0);

  glVertex3f(-1.0, 1.0, 1.0);
  glVertex3f(-1.0, -1.0, 1.0);

  // Sides
  glVertex3f(-1.0, -1.0, -1.0);
  glVertex3f(-1.0, -1.0, 1.0);

  glVertex3f(1.0, -1.0, -1.0);
  glVertex3f(1.0, -1.0, 1.0);

  // glVertex3f(1.0, 1.0, -1.0);
  // glVertex3f(1.0, 1.0, 1.0);

  // glVertex3f(-1.0, 1.0, -1.0);
  // glVertex3f(-1.0, 1.0, 1.0);

  glEnd();
}
