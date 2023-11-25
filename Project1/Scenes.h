#ifndef SCENES_H
#define SCENES_H

#include <glut.h>
#include <vector>
#include <algorithm>
#include <iostream>
#include <sstream>

#include "Ball.h"
#include "Box.h"
#include "Commands.h"
#include "Collision.h"
using namespace std;

void drawMainScene();
void drawNextFruitScene();
void drawHoldScene();
void drawGameOverScene();
void drawRankings();

void showScoreScene();
void showHoldText();

extern int scoreRanking[3];
extern string holdText;
extern bool gameOver;
extern bool prevGameOver;
#endif