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

    ball.x += ball.vx;  // �ӵ��� ���� ���� ��ġ ����
    ball.y += ball.vy;
    ball.z += ball.vz;

    ball.vy -= 0.001;  // gravity

    // ���� ���� �浹
    if (ball.x - ball.radius < -2) {
      ball.vx = -0.1f * ball.vx;  // ������� ����ʿ� ���� �浹 ���Ⱑ �����
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

    // ���� �������� �浹 �˻�
    for (auto& other : balls) {
      if (&ball != &other && areColliding(ball, other)) {
        handleCollision(ball, other);
      }
    }
  }
  glColor3f(1.0f, 0.0f, 0.0f);  // ������
  glPushMatrix();
  glTranslatef(marker_x, marker_y, marker_z);
  glutSolidSphere(0.1, 20, 20);  // ���⿡ ������ ���� ���� ǥ��
  glPopMatrix();

  glColor3f(1.0f, 0.0f, 0.0f);
  glBegin(GL_LINES);
  glVertex3f(marker_x, -2.0f, marker_z);  // �ڽ� �ٴں��� õ����� �̾���
  glVertex3f(marker_x, 2.5f, marker_z);
  glEnd();

  glColor3f(1.0f, 1.0f, 1.0f);  // �ٽ� ������� ����
}