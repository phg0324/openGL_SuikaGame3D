#include "Commands.h"

int window_width = 1920;
int window_height = 1080;

float camera_distance = 7.0f;  // 카메라와 상자 사이의 거리
float camera_angle = 0.0f;     // 카메라 각도
float min_distance = 6.0f;     // 카메라와 상자의 최소 거리
float max_distance = 13.0f;    // 카메라와 상자의 최소 거리

float marker_x = 0.0f, marker_y = 2.0f, marker_z = 0.0f;

std::vector<Ball> balls;
std::chrono::steady_clock::time_point last_space_time;

bool blockSwap = false;         // 연속적인 홀드를 방지

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
            min_distance) {  // 카메라가 상자에 너무 가깝지 않은 경우에만 이동
          camera_distance -= 1.0f;  // 카메라를 상자에 가깝게 이동
        }
        break;
      case 's':
        if (camera_distance < max_distance) {  // 동일
          camera_distance += 1.0f;  // 카메라를 상자에서 멀어지게 이동
        }
        break;
      case 'a':
        camera_angle += M_PI / 180.0f * 2;  // 카메라를 왼쪽으로 회전
        break;
      case 'd':
        camera_angle -= M_PI / 180.0f * 2;  // 카메라를 오른쪽으로 회전
        break;
      case ' ':  // 스페이스 바 입력시 공 생성 case문안에서 선언하거나
                 // 초기화할때는 중괄호가 있어야함
      {
        auto now = std::chrono::steady_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(
            now - last_space_time);
        /*
        if (duration.count() < 1000) {
          // 스페이스바를 누른지 1초가 지나지 않았으면 무시
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
      case 9:  // tab키 입력시 홀드 기능
        if (blockSwap == false) {
          int front = nextFruit.front();
          if (hold != -1) {
            nextFruit[0] = hold;
            hold = front;
          } else {  // 홀드를 한번도 사용하지 않은경우
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

void special(int key, int x, int y) {  // 화살표키 조종
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

  // 표시가 박스를 벗어나지 않도록 최대, 최소값 설정

  marker_x = std::max(-2.0f, std::min(2.0f, marker_x));

  marker_z = std::max(-2.0f, std::min(2.0f, marker_z));

  glutPostRedisplay();
}



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