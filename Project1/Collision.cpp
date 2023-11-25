#include "Collision.h"
#include "Commands.h"
#include <cmath>

/*
//////////////////////////////////////////////////////////////////////////////////////////




        handle Coliisions




////////////////////////////////////////////////////////////////////////////////////////////
*/

float restitution = 0.0001; // 반발계수, 높아지면 더 세게 튕겨짐
int score = 0;

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

  // 충돌에 따른 속도 변화. y축 아래 방향의 속도 변화는 무시

  a.vx += j * nx / a.mass;
  a.vy += j * ny / a.mass; 
  a.vz += j * nz / a.mass;
  b.vx -= j * nx / b.mass;
  b.vy -= j * ny / b.mass; 
  b.vz -= j * nz / b.mass;

  // 마찰력에 의한 속도의 변화, 각 공의 속도를 독립적으로 계산
  friction(a);
  friction(b);

  /*
  float slideFactor = 0.00001f;  // 미끄러짐 정도를 조절하는 인자
  if (a.mass > b.mass && a.y < b.y && a.x == b.x) {
    a.vx += (rand() % 2 ? -1 : 1) * slideFactor;
    a.vz += (rand() % 2 ? -1 : 1) * slideFactor;
  } else if (b.mass > a.mass && b.vy < a.vy) {
    b.vx += (rand() % 2 ? -1 : 1) * slideFactor;
    b.vz += (rand() % 2 ? -1 : 1) * slideFactor;
  }
  */
  // 공들의 위치를 수정하여 겹치지 않도록 함, 각 공의 반지름을 기반으로 계산
  float overlap = a.radius + b.radius - n_length;
  if (overlap > 0) {
    a.x += overlap * nx * (b.radius / (a.radius + b.radius));
    a.y += overlap * ny * (b.radius / (a.radius + b.radius));
    a.z += overlap * nz * (b.radius / (a.radius + b.radius));
    b.x -= overlap * nx * (a.radius / (a.radius + b.radius));
    b.y -= overlap * ny * (a.radius / (a.radius + b.radius));
    b.z -= overlap * nz * (a.radius / (a.radius + b.radius));
  }
}
void  friction(Ball& a) {
  float friction = 0.1f;
  a.vx -= friction * a.vx;
  a.vy -= friction * a.vy;
  a.vz -= friction * a.vz;
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
    friction(ball);
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
  score += a.radius * 100;
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

bool outSideBox(Ball& a) { 
    if (a.y > 2.1) {
        return true;
    } else {
        return false;
    }
}
