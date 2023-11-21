#ifndef BALL_H
#define BALL_H

#include <random>

class Ball {
 public:
  float x, y, z;
  float vx, vy, vz;  // x, y, z 각각의 속도
  float mass;
  float radius;

  Ball();  // 생성자 선언
};

#endif