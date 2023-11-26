#ifndef SCENES_H
#define SCENES_H

#include <glut.h>
#include <glu.h>
#include <glaux.h>
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
void texturing();
void backgroundTexturing();
void switchTL(bool trig);
void drawBall(int t, GLfloat transX, GLfloat transY, GLfloat transZ);

extern int scoreRanking[3];
extern string holdText;
extern bool gameOver;
extern bool prevGameOver;


extern unsigned int ids[12];
extern AUX_RGBImageRec* tex[12];
extern GLUquadric* sphere;

extern AUX_RGBImageRec* bgImage;
extern GLuint bgTexture;

#endif