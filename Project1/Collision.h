#ifndef COLLISION_H
#define COLLISION_H

#include "Ball.h"

bool areColliding(const Ball& a, const Ball& b);
void handleCollision(Ball& a, Ball& b);

#endif