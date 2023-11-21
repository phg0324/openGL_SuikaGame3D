#include "Collision.h"
#include <cmath>

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
  float overlap =
      a.radius + b.radius - n_length;  // 공들의 반지름 합을 n_length와 비교
  if (overlap > 0) {
    a.x += overlap / 2 * nx;
    a.y += overlap / 2 * ny;
    a.z += overlap / 2 * nz;
    b.x -= overlap / 2 * nx;
    b.y -= overlap / 2 * ny;
    b.z -= overlap / 2 * nz;
  }
}
