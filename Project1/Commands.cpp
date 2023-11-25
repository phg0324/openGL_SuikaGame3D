#include "Commands.h"

int window_width = 1920;
int window_height = 1080;

float camera_distance = 7.0f;  // ī�޶�� ���� ������ �Ÿ�
float camera_angle = 0.0f;     // ī�޶� ����
float min_distance = 6.0f;     // ī�޶�� ������ �ּ� �Ÿ�
float max_distance = 13.0f;    // ī�޶�� ������ �ּ� �Ÿ�

float marker_x = 0.0f, marker_y = 2.0f, marker_z = 0.0f;

std::vector<Ball> balls;
std::chrono::steady_clock::time_point last_space_time;

bool blockSwap = false;         // �������� Ȧ�带 ����

void keyboard(unsigned char keyPressed, int x, int y) {
  keyPressed = tolower(keyPressed);
  if (gameOver) {
    if (keyPressed == 'r') {
      balls.clear();
      hold = -1;
      gameOver = false;
      score = 0;
    }

  } else {
    switch (keyPressed) {
      case 'w':
        if (camera_distance >
            min_distance) {  // ī�޶� ���ڿ� �ʹ� ������ ���� ��쿡�� �̵�
          camera_distance -= 1.0f;  // ī�޶� ���ڿ� ������ �̵�
        }
        break;
      case 's':
        if (camera_distance < max_distance) {  // ����
          camera_distance += 1.0f;  // ī�޶� ���ڿ��� �־����� �̵�
        }
        break;
      case 'a':
        camera_angle += M_PI / 180.0f * 2;  // ī�޶� �������� ȸ��
        break;
      case 'd':
        camera_angle -= M_PI / 180.0f * 2;  // ī�޶� ���������� ȸ��
        break;
      case ' ':  // �����̽� �� �Է½� �� ���� case���ȿ��� �����ϰų�
                 // �ʱ�ȭ�Ҷ��� �߰�ȣ�� �־����
      {
        auto now = std::chrono::steady_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(
            now - last_space_time);
        /*
        if (duration.count() < 1000) {
          // �����̽��ٸ� ������ 1�ʰ� ������ �ʾ����� ����
          break;
        }
        */
        last_space_time = now;

        blockSwap = false;
        Ball ball;
        ball.x = marker_x;
        ball.y = marker_y;
        ball.z = marker_z;
        ball.vx = ball.vy = ball.vz = 0;

        ball.type = nextFruit.front();
        nextFruit.erase(nextFruit.begin());
        addFruit();
        ball.radius = fruitSize.find(ball.type)->second;
        ball.mass = fruitWeight.find(ball.type)->second;
        ball.colorR = fruitColor.find(ball.type)->second[0];
        ball.colorG = fruitColor.find(ball.type)->second[1];
        ball.colorB = fruitColor.find(ball.type)->second[2];
        ball.colorA = fruitColor.find(ball.type)->second[3];

        balls.push_back(ball);
      } break;
      case 'r':
        balls.clear();
        hold = -1;
        gameOver = false;
        score = 0;
        break;
      case 9:  // tabŰ �Է½� Ȧ�� ���
        if (blockSwap == false) {
          int front = nextFruit.front();
          if (hold != -1) {
            nextFruit[0] = hold;
            hold = front;
          } else {  // Ȧ�带 �ѹ��� ������� �������
            hold = front;
            nextFruit.erase(nextFruit.begin());
            addFruit();
          }
          blockSwap = true;
        }
        break;
    }
  }
  glutPostRedisplay();
}

void special(int key, int x, int y) {  // ȭ��ǥŰ ����
  if (gameOver){
    return;
  }
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

  // ǥ�ð� �ڽ��� ����� �ʵ��� �ִ�, �ּҰ� ����

  marker_x = std::max(-2.0f, std::min(2.0f, marker_x));

  marker_z = std::max(-2.0f, std::min(2.0f, marker_z));

  glutPostRedisplay();
}



// Ŭ������ �� ���� (�̻��)
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


    gluUnProject(win_x, win_y, 0.0, modelview, projection, viewport, &d_x,
&d_y, &d_z);

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