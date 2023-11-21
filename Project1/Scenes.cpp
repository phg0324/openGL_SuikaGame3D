#include "Scenes.h"


void drawMainScene() {
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