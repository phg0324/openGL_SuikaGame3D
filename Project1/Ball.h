#ifndef BALL_H
#define BALL_H

#include <random>

class Ball {
 public:
  float x, y, z;
  float vx, vy, vz;  // x, y, z ������ �ӵ�
  float mass;
  float radius;

  Ball();  // ������ ����
};

#endif