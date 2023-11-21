#include "Collision.h"
#include <cmath>

/*
//////////////////////////////////////////////////////////////////////////////////////////




        handle Coliisions




////////////////////////////////////////////////////////////////////////////////////////////
*/

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
  float e = 0.1f;  // �ݹ߰��, �������� �� ���� ƨ����
  float j = -(1.0f + e) * (rvx * nx + rvy * ny + rvz * nz) /
            (1.0f / a.mass + 1.0f / b.mass);

  // �浹�� ���� �ӵ��� ��ȭ
  a.vx += j * nx / a.mass;
  a.vy += j * ny / a.mass;
  a.vz += j * nz / a.mass;
  b.vx -= j * nx / b.mass;
  b.vy -= j * ny / b.mass;
  b.vz -= j * nz / b.mass;

  // ������ ��ġ�� �����Ͽ� ��ġ�� �ʵ��� ��
  float overlap =
      a.radius + b.radius - n_length;  // ������ ������ ���� n_length�� ��
  if (overlap > 0) {
    a.x += overlap / 2 * nx;
    a.y += overlap / 2 * ny;
    a.z += overlap / 2 * nz;
    b.x -= overlap / 2 * nx;
    b.y -= overlap / 2 * ny;
    b.z -= overlap / 2 * nz;
  }
}
