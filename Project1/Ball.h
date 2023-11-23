#ifndef BALL_H
#define BALL_H
#include <glut.h>
#include <glu.h>
#include <random>
#include <map>
#include <vector>
#include <queue>
using namespace std;

class Ball {
 public:
  float x, y, z;
  float vx, vy, vz;  // x, y, z 각각의 속도
  float mass;
  float radius;

  GLfloat colorR;
  GLfloat colorG;
  GLfloat colorB;
  GLfloat colorA;

  int type; 
  /*
  bool operator==(const Ball& other) const {
    return x == other.x && y == other.y && z == other.z && type == other.type &&
           radius == other.radius;
  }
  */
  Ball();  // 생성자 선언
};
void fruits();
void addFruit();
extern map<int, float> fruitSize;
extern map<int, float> fruitWeight;
extern map<int, std::vector<GLfloat>> fruitColor;

extern vector<int> nextFruit;
extern int hold;

#endif
