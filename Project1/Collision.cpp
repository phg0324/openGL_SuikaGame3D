#include "Collision.h"
#include "Commands.h"
#include <cmath>

/*
//////////////////////////////////////////////////////////////////////////////////////////




        handle Coliisions




////////////////////////////////////////////////////////////////////////////////////////////
*/

float restitution = 0.0001; // 반발계수, 높아지면 더 세게 튕겨짐

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

  float j = -(1.0f + restitution) * (rvx * nx + rvy * ny + rvz * nz) /
            (1.0f / a.mass + 1.0f / b.mass);

  // 충돌에 따른 속도의 변화
  a.vx += j * nx / a.mass;
  a.vy += j * ny / a.mass;
  a.vz += j * nz / a.mass;
  b.vx -= j * nx / b.mass;
  b.vy -= j * ny / b.mass;
  b.vz -= j * nz / b.mass;


   // 마찰력에 의한 속도의 변화
  float friction = 0.1f;  // 마찰계수, 높아지면 마찰력이 커짐
  a.vx -= friction * rvx;
  a.vy -= friction * rvy;
  a.vz -= friction * rvz;
  b.vx += friction * rvx;
  b.vy += friction * rvy;
  b.vz += friction * rvz;


  // 공들의 위치를 수정하여 겹치지 않도록 함
  float overlap =
      a.radius + b.radius - n_length;  // 공들의 반지름 합을 n_length와 비교
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
  // 벽과 공의 충돌
  if (ball.x - ball.radius < -2) {
    ball.vx =
        -restitution * ball.vx;  // 상수값이 변경됨에 따라 충돌 세기가 변경됨
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
  //현재 a와 b가 생김세가 동일하기 때문에 동시에 지워지는중 고치셈

}

