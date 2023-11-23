#include "Collision.h"
#include "Commands.h"
#include <cmath>

/*
//////////////////////////////////////////////////////////////////////////////////////////




        handle Coliisions




////////////////////////////////////////////////////////////////////////////////////////////
*/

float restitution = 0.0001; // �ݹ߰��, �������� �� ���� ƨ����

// ���� ���� �浹������ Ȯ��
bool areColliding(const Ball& a, const Ball& b) {
  float dx = a.x - b.x;
  float dy = a.y - b.y;
  float dz = a.z - b.z;
  float distance = std::sqrt(dx * dx + dy * dy + dz * dz);
  return distance < a.radius + b.radius;
}

void handleCollision(Ball& a, Ball& b) {
  // normal vector ���
  float nx = a.x - b.x;
  float ny = a.y - b.y;
  float nz = a.z - b.z;
  float n_length = std::sqrt(nx * nx + ny * ny + nz * nz);
  nx /= n_length;
  ny /= n_length;
  nz /= n_length;

  // ��� �ӵ� ���
  float rvx = a.vx - b.vx;
  float rvy = a.vy - b.vy;
  float rvz = a.vz - b.vz;

  // ź�� �浹 ����

  float j = -(1.0f + restitution) * (rvx * nx + rvy * ny + rvz * nz) /
            (1.0f / a.mass + 1.0f / b.mass);

  // �浹�� ���� �ӵ��� ��ȭ
  a.vx += j * nx / a.mass;
  a.vy += j * ny / a.mass;
  a.vz += j * nz / a.mass;
  b.vx -= j * nx / b.mass;
  b.vy -= j * ny / b.mass;
  b.vz -= j * nz / b.mass;


   // �����¿� ���� �ӵ��� ��ȭ
  float friction = 0.1f;  // �������, �������� �������� Ŀ��
  a.vx -= friction * rvx;
  a.vy -= friction * rvy;
  a.vz -= friction * rvz;
  b.vx += friction * rvx;
  b.vy += friction * rvy;
  b.vz += friction * rvz;


  // ������ ��ġ�� �����Ͽ� ��ġ�� �ʵ��� ��
  float overlap =
      a.radius + b.radius - n_length;  // ������ ������ ���� n_length�� ��
  if (overlap > 0) {
    float total_mass = a.mass + b.mass;
    a.x += overlap * nx * (b.mass / total_mass);
    a.y += overlap * ny * (b.mass / total_mass);
    a.z += overlap * nz * (b.mass / total_mass);
    b.x -= overlap * nx * (a.mass / total_mass);
    b.y -= overlap * ny * (a.mass / total_mass);
    b.z -= overlap * nz * (a.mass / total_mass);
  }
}


void colideWall(Ball& ball) {
  // ���� ���� �浹
  if (ball.x - ball.radius < -2) {
    ball.vx =
        -restitution * ball.vx;  // ������� ����ʿ� ���� �浹 ���Ⱑ �����
    ball.x = -2 + ball.radius;
  } else if (ball.x + ball.radius > 2) {
    ball.vx = -restitution * ball.vx;
    ball.x = 2 - ball.radius;
  }

  if (ball.y - ball.radius < -2) {
    ball.vy = -restitution * ball.vy;
    ball.y = -2 + ball.radius;
  }

  if (ball.z - ball.radius < -2) {
    ball.vz = -restitution * ball.vz;
    ball.z = -2 + ball.radius;
  } else if (ball.z + ball.radius > 2) {
    ball.vz = -restitution * ball.vz;
    ball.z = 2 - ball.radius;
  }
}


void combineBalls(Ball& a, Ball& b) {

  a.x = (a.x + b.x) / 2;
  a.y = (a.y + b.y) / 2;
  a.z = (a.z + b.z) / 2;
  a.type = a.type + 1;
  a.radius = fruitSize.find(a.type)->second; 
  a.mass = fruitWeight.find(a.type)->second;
  a.colorR = fruitColor.find(a.type)->second[0];
  a.colorG = fruitColor.find(a.type)->second[1];
  a.colorB = fruitColor.find(a.type)->second[2];
  a.colorA = fruitColor.find(a.type)->second[3];

  /*
  for (auto it = balls.begin(); it != balls.end(); ++it) {
    if (&(*it) == &b) {
      balls.erase(it);
      break;
    }
  }
  */
  //���� a�� b�� ���輼�� �����ϱ� ������ ���ÿ� ���������� ��ġ��

}

