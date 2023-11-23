#include "Scenes.h"


void drawMainScene() {
  glPushMatrix();
  glScalef(2.0, 2.0, 2.0);
  drawWireBoxWithoutTop();
  glPopMatrix();

  std::vector<int> balls_to_remove;

  for (auto& ball : balls) {
    glPushMatrix();
    glColor4f(ball.colorR, ball.colorG, ball.colorB, ball.colorA);
    glTranslatef(ball.x, ball.y, ball.z);
    glutSolidSphere(ball.radius, 100, 100);
    glPopMatrix();

    ball.x += ball.vx;  // �ӵ��� ���� ���� ��ġ ����
    ball.y += ball.vy;
    ball.z += ball.vz;

    ball.vy -= 0.001;  // gravity

    colideWall(ball); 

    // ���� �������� �浹 �˻�
    for (int i = 0; i < balls.size(); i++) {
      Ball& other = balls[i];
      if (&ball != &other && areColliding(ball, other)) {
        if (ball.type == other.type) {
          combineBalls(ball, other);
          balls_to_remove.push_back(i);
        } else {
          handleCollision(ball, other);
        }
      }
    }
  }

  std::sort(balls_to_remove.begin(), balls_to_remove.end(),
            std::greater<>());
  // ���� �ε������� ����
  for (int index : balls_to_remove) {
    balls.erase(balls.begin() + index);
  }
  balls_to_remove.clear();

  int type = nextFruit[0];
  float radius = fruitSize.find(type)->second;
  float mass = fruitWeight.find(type)->second;
  GLfloat r = fruitColor.find(type)->second[0];
  GLfloat g = fruitColor.find(type)->second[1];
  GLfloat b = fruitColor.find(type)->second[2];
  GLfloat a = fruitColor.find(type)->second[3];

  glColor4f(r,g,b,a); 
  glPushMatrix();
  glTranslatef(marker_x, marker_y, marker_z);
  glutSolidSphere(radius, 20, 20);  // ���⿡ ������ ���� ���� ǥ��
  glPopMatrix();

  glColor3f(1.0f, 0.0f, 0.0f);
  glBegin(GL_LINES);
  glVertex3f(marker_x, -2.0f, marker_z);  // �ڽ� �ٴں��� õ����� �̾���
  glVertex3f(marker_x, 2.5f, marker_z);
  glEnd();

  glColor3f(1.0f, 1.0f, 1.0f);  // �ٽ� ������� ����
}

void drawNextFruitScene() {
  int distance = 1;
  int i = 0;


  for (int i = 1; i < 5; i++) {
    int type = nextFruit[i];  
    float radius = fruitSize.find(type)->second;
    float mass = fruitWeight.find(type)->second;
    GLfloat r = fruitColor.find(type)->second[0];
    GLfloat g = fruitColor.find(type)->second[1];
    GLfloat b = fruitColor.find(type)->second[2];
    GLfloat a = fruitColor.find(type)->second[3];

    glPushMatrix();
    glColor4f(r, g, b, a);
    glTranslatef(0, 13-i, 0);

    glutSolidSphere(radius, 100, 100);
    glPopMatrix();

  }
  glColor3f(1.0f, 1.0f, 1.0f);
}

void drawHoldScene() {

   if (hold != -1) {
    int type = hold;

    float radius = fruitSize.find(type)->second;
    float mass = fruitWeight.find(type)->second;
    GLfloat r = fruitColor.find(type)->second[0];
    GLfloat g = fruitColor.find(type)->second[1];
    GLfloat b = fruitColor.find(type)->second[2];
    GLfloat a = fruitColor.find(type)->second[3];

    glColor4f(r, g, b, a);
    glPushMatrix();
    glTranslatef(0, 20, 0);
    glutSolidSphere(radius, 20, 20); 
    glPopMatrix();

    glColor3f(1.0f, 1.0f, 1.0f);
  }

}