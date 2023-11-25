#ifndef COLLISION_H
#define COLLISION_H

#include "Ball.h"

bool areColliding(const Ball& a, const Ball& b);
void handleCollision(Ball& a, Ball& b);
void combineBalls(Ball& a, Ball& b);
void colideWall(Ball& a);
void friction(Ball& a);
bool outSideBox(Ball& a);

extern float restitution;
extern int score;
#endif