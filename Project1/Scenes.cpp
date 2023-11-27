#include "Scenes.h"

#pragma comment(lib, "glaux.lib")
#pragma comment(lib, "legacy_stdio_definitions.lib")

bool gameOver = false;
bool prevGameOver = false;
int scoreRanking[3];

unsigned int ids[12];
AUX_RGBImageRec* tex[12];
GLUquadric* sphere;

AUX_RGBImageRec* bgImage;
GLuint bgTexture;


GLfloat diffuse0[];
GLfloat no_emission[];
GLfloat light_emission[];


void drawMainScene() {

  
  glColor3f(1.0f, 1.0f, 1.0f);  // 다시 흰색으로 복구
  std::vector<int> balls_to_remove;

  for (auto& ball : balls) {
    glPushMatrix();

    switchTL(true);

    if (outSideBox(ball)) {
      GLfloat flicker = (sin(glutGet(GLUT_ELAPSED_TIME) * 0.01) + 1.0) /
                        2.0;  // 0.0 ~ 1.0 사이의 값
      glColor4f(ball.colorR * flicker, ball.colorG * flicker,
                ball.colorB * flicker, ball.colorA);
    } else {
      glColor4f(ball.colorR, ball.colorG, ball.colorB, ball.colorA);
    }

    GLfloat rgbaColor[] = {ball.colorR, ball.colorG, ball.colorB, ball.colorA}; 

    glTranslatef(ball.x, ball.y, ball.z);

    glMaterialfv(GL_FRONT, GL_EMISSION, light_emission);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse0);
    glMaterialfv(GL_FRONT, GL_AMBIENT, rgbaColor);
    glBindTexture(GL_TEXTURE_2D, ids[ball.type]);

    gluSphere(sphere,ball.radius, 100, 100);

    switchTL(false);

    glPopMatrix();

    if (gameOver) {
      // 게임이 종료된 경우 ball의 움직임을 멈춤
      continue;
    }

    ball.x += ball.vx;  // 속도에 따른 공의 위치 변경
    ball.y += ball.vy;
    ball.z += ball.vz;

    ball.vy -= 0.0005;  // gravity

    colideWall(ball);
  }
    // 공과 공사이의 충돌 검사
  for (int i = 0; i < balls.size(); i++) {
    Ball& ball = balls[i];
    for (int j = i + 1; j < balls.size(); j++) {
      Ball& other = balls[j];
      if (areColliding(ball, other)) {
        if (ball.type == other.type) {
          combineBalls(ball, other);
          balls_to_remove.push_back(j);
        } else {
          handleCollision(ball, other);
        }
      }
    }
    if (outSideBox(ball)) {
      gameOver = true;
    }
    
 }
  if (!prevGameOver && gameOver) {
    if (score > scoreRanking[2]) {
      scoreRanking[2] = score;
    }
    sort(scoreRanking, scoreRanking + 3, greater<int>());
  }

  prevGameOver = gameOver;
  std::sort(balls_to_remove.begin(), balls_to_remove.end(),
            std::greater<>());
  // 높은 인덱스부터 제거
  for (int i = 0; i < balls_to_remove.size(); i++) {
    if (i < balls_to_remove.size() - 1) {
      if (balls_to_remove[i] == balls_to_remove[i + 1]) {
        continue;
      }
    }
    balls.erase(balls.begin() + balls_to_remove[i]);
  }
  balls_to_remove.clear();

  int type = nextFruit[0];
  
  drawBall(type, marker_x, marker_y,marker_z);

  glColor3f(1.0f, 0.0f, 0.0f);
  glBegin(GL_LINES);
  glVertex3f(marker_x, -2.0f, marker_z);  // 박스 바닥부터 천장까지 이어줌
  glVertex3f(marker_x, 2.0f, marker_z);
  glEnd();

  glColor3f(1.0f, 1.0f, 1.0f);  // 다시 흰색으로 복구

  switchTL(false);


  glPushMatrix();
  glColor3f(0.5, 0.5, 0.5);
  glScalef(2.0, 2.0, 2.0);
  drawBoxLine();
  
  glPopMatrix();

  glPushMatrix();
  glColor3f(0.5, 0, 0);
  glScalef(2.0, 2.0, 2.0);
  drawBoxTop();
  glPopMatrix();


  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  glPushMatrix();
  glColor4f(1.0, 1.0, 1.0, 0.1);
  glScalef(2.0, 2.0, 2.0);
  drawWireBoxWithoutTop();
  drawBoxBottom();
  
  glPopMatrix();
  
  glDisable(GL_BLEND);

  
}

void drawNextFruitScene() {
  int distance = 1;
  int i = 0;

  glRasterPos2f(-1.0f, 12.4f);

  // 문자열 출력
  for (char c : "Next") {
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
  }

  for (int i = 1; i < 5; i++) {
    int type = nextFruit[i];  

    glPushMatrix();
    glTranslatef(0, 13-i, 0);
    glColor3f(1.0f, 1.0f, 1.0f);

    glBegin(GL_LINE_LOOP);
    glVertex2f(-0.5, -0.5);
    glVertex2f(-0.5, 0.5);
    glVertex2f(0.5, 0.5);
    glVertex2f(0.5, -0.5);
    glEnd();
    glPopMatrix();

    drawBall(type, 0, 13 - i, 0);
  }
  glColor3f(1.0f, 1.0f, 1.0f);
}
string holdText = "Tab to Hold";

void drawHoldScene() {

    showScoreScene();
    
    showHoldText();

    glPushMatrix();
    glTranslatef(0, 20, 0);
    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_LINE_LOOP);
    glVertex2f(-0.75, -0.75);
    glVertex2f(-0.75, 0.75);
    glVertex2f(0.75, 0.75);
    glVertex2f(0.75, -0.75);
    glEnd();
    glPopMatrix();

   if (hold != -1) {
    int type = hold;
    holdText = "Hold";

    drawBall(type, 0, 20, 0);

    glColor3f(1.0f, 1.0f, 1.0f);
  }
}

void showHoldText() {
  glRasterPos2f(-0.5f, 20.5f);

  // 문자열 출력
  for (char c : holdText) {
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
  }
}

void showScoreScene() {
  // 점수 출력 위치 설정
  glRasterPos2f(0.0f, 19.0f);

  // 점수 문자열로 변환
  std::stringstream ss;
  ss << "Score: " << score;
  std::string scoreStr = ss.str();

  // 문자열 출력
  for (char c : scoreStr) {
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
  }
}

void drawGameOverScene() {

  glMatrixMode(GL_PROJECTION);
  glPushMatrix(); 
  glLoadIdentity();
  gluOrtho2D(0.0, window_width, 0.0,
                window_height);  // Set up an orthographic projection
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  glColor3f(1.0f, 1.0f, 1.0f);

  glRasterPos2f(window_width / 2 - 50, window_height / 2 + 40);

  for (char c : "Game Over") {
      glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
  }

  glRasterPos2f(window_width / 2 - 50, window_height / 2);
  for (char c : "Score: " + std::to_string(score)) {
      glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
  }

  glRasterPos2f(window_width / 2 - 50, window_height / 2 - 40);
  for (char c : "Press R to restart") {
      glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
  }
  
  glMatrixMode(GL_PROJECTION);
  glPopMatrix();  
  glMatrixMode(GL_MODELVIEW);
}

void drawRankings(){
  glMatrixMode(GL_PROJECTION);
  glPushMatrix();
  glLoadIdentity();
  gluOrtho2D(0.0, window_width, 0.0, window_height);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  glColor3f(1.0f, 1.0f, 1.0f);

  glRasterPos2f(50, window_height / 2 + 40);

  for (char c : "Top Scores") {
      glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
  }

  for (int i = 0; i < 3; i++) {
      glRasterPos2f(50, window_height / 2 + 30 - 30 * (i + 1));  // 위치 조정
      for (char c : to_string(i+1) + ". "+ to_string(scoreRanking[i])) {
      glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
      }

      // 선으로 라인 구분, 선의 길이 조정
      glBegin(GL_LINES);
      glVertex2f(50, window_height / 2 - 5  - 30 * i);
      glVertex2f(50 + glutBitmapWidth(GLUT_BITMAP_HELVETICA_18, '0') * 10,
                 window_height / 2 - 5  - 30 * i);
      glEnd();
  }
  glMatrixMode(GL_PROJECTION);
  glPopMatrix();
  glMatrixMode(GL_MODELVIEW);
}

void drawHelp(){
  glMatrixMode(GL_PROJECTION);
  glPushMatrix();
  glLoadIdentity();
  gluOrtho2D(0.0, window_width, 0.0, window_height);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  glColor3f(0.5f, 0.75f, 1.0f);

  glRasterPos2f(50, 200);

  for (char c : "Move Camera: W A S D") {
      glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
  }
  glRasterPos2f(50, 170);
  for (char c : "Move Fruit: Arrow Keys") {
      glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
  }
  glRasterPos2f(50, 140);
  for (char c : "Deploy Fruit: Space Bar") {
      glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
  }
  glRasterPos2f(50, 110);
  for (char c : "Hold Fruit: Tab Key") {
      glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
  }
  glRasterPos2f(50, 80);
  for (char c : "Restart Game: R ") {
      glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
  }
  glMatrixMode(GL_PROJECTION);
  glPopMatrix();
  glMatrixMode(GL_MODELVIEW);
}
void texturing() {

  tex[0] = auxDIBImageLoad("textures/Cherry.bmp");
  tex[1] = auxDIBImageLoad("textures/Strawberry.bmp");
  tex[2] = auxDIBImageLoad("textures/Grape.bmp");
  tex[3] = auxDIBImageLoad("textures/Orange.bmp");
  tex[4] = auxDIBImageLoad("textures/Persimmon.bmp");
  tex[5] = auxDIBImageLoad("textures/Apple.bmp");
  tex[6] = auxDIBImageLoad("textures/Pear.bmp");
  tex[7] = auxDIBImageLoad("textures/Peach.bmp");
  tex[8] = auxDIBImageLoad("textures/Pineapple.bmp");
  tex[9] = auxDIBImageLoad("textures/Melon.bmp");
  tex[10] = auxDIBImageLoad("textures/Watermelon.bmp");
  tex[11] = auxDIBImageLoad("textures/Background.bmp");

  for (int i = 0; i < 12; i++) {
      glGenTextures(1, &ids[i]);
      glBindTexture(GL_TEXTURE_2D, ids[i]);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
      glTexImage2D(GL_TEXTURE_2D, 0, 3, tex[i]->sizeX, tex[i]->sizeY, 0, GL_RGB,
                   GL_UNSIGNED_BYTE, tex[i]->data);
      glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
  }

  glEnable(GL_TEXTURE_2D);
  glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

  sphere = gluNewQuadric();
  gluQuadricDrawStyle(sphere, GLU_FILL);
  gluQuadricNormals(sphere, GLU_SMOOTH);
  gluQuadricOrientation(sphere, GLU_OUTSIDE);
  gluQuadricTexture(sphere, GL_TRUE);
}

void backgroundTexturing() {
  glDisable(GL_TEXTURE_GEN_S);
  glDisable(GL_TEXTURE_GEN_T);

  glEnable(GL_LIGHTING);
  glEnable(GL_TEXTURE_2D);
  glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

  glMatrixMode(GL_PROJECTION);  
  glPushMatrix();              
  glLoadIdentity();             
  gluOrtho2D(0.0, window_width, 0.0, window_height);  

  glMatrixMode(GL_MODELVIEW);  
  glPushMatrix();              
  glLoadIdentity();            

  glDisable(GL_DEPTH_TEST);  // 깊이 테스트 비활성화

  glBindTexture(GL_TEXTURE_2D, ids[11]);
  glBegin(GL_QUADS);
  glTexCoord2f(0.0f, 0.0f);
  glVertex2f(0.0f, 0.0f);
  glTexCoord2f(1.0f, 0.0f);
  glVertex2f(window_width, 0.0f);
  glTexCoord2f(1.0f, 1.0f);
  glVertex2f(window_width, window_height);
  glTexCoord2f(0.0f, 1.0f);
  glVertex2f(0.0f, window_height);
  glEnd();

  glEnable(GL_DEPTH_TEST);  

  glPopMatrix();  

  glMatrixMode(GL_PROJECTION);  
  glPopMatrix();  

  glMatrixMode(GL_MODELVIEW);  

  glDisable(GL_TEXTURE_2D);
  glDisable(GL_LIGHTING);
}

void switchTL(bool trig) { 
    if (trig) {
      glEnable(GL_LIGHTING);
      glEnable(GL_TEXTURE_2D);
    }
    else {
      glDisable(GL_TEXTURE_2D);
      glDisable(GL_LIGHTING); 
    }
}

void drawBall(int t, GLfloat transX, GLfloat transY, GLfloat transZ) {
    float radius = fruitSize.find(t)->second;
    float mass = fruitWeight.find(t)->second;
    GLfloat r = fruitColor.find(t)->second[0];
    GLfloat g = fruitColor.find(t)->second[1];
    GLfloat b = fruitColor.find(t)->second[2];
    GLfloat a = fruitColor.find(t)->second[3];

    GLfloat rgbaColor[] = {r,g,b,a};
    switchTL(true);


    glPushMatrix();
    glTranslatef(transX, transY, transZ);
    glMaterialfv(GL_FRONT, GL_EMISSION, light_emission);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse0);
    glMaterialfv(GL_FRONT, GL_AMBIENT, rgbaColor);
    glBindTexture(GL_TEXTURE_2D, ids[t]);
    gluSphere(sphere,radius, 100, 100);  
    glPopMatrix();

    switchTL(false);


}
