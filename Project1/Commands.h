#ifndef COMMANDS_H
#define COMMANDS_H
#define _USE_MATH_DEFINES

#include <glut.h>
#include <vector>
#include "Ball.h"
#include <cmath>
#include <cctype>

using namespace std;

void keyboard(unsigned char keyPressed, int x, int y);

void special(int key, int x, int y);

//void mouse(int button, int state, int x, int y);

extern int window_width;
extern int window_height;

extern float camera_distance;  // ī�޶�� ���� ������ �Ÿ�
extern float camera_angle;      // ī�޶� ����
extern float min_distance;      // ī�޶�� ������ �ּ� �Ÿ�
extern float max_distance;      // ī�޶�� ������ �ּ� �Ÿ�

extern float marker_x, marker_y, marker_z;

extern std::vector<Ball> balls;

#endif