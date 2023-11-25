#include "Scenes.h"

bool gameOver = false;
bool prevGameOver = false;
int scoreRanking[3];

void drawMainScene() {
  glPushMatrix();
  glScalef(2.0, 2.0, 2.0);
  drawWireBoxWithoutTop();
  glPopMatrix();

  glPushMatrix();

  glColor3f(0.5,0,0);
  glScalef(2.0, 2.0, 2.0);
  drawBoxTop();

  glPopMatrix();

  glColor3f(1.0f, 1.0f, 1.0f);  // 다시 흰색으로 복구
  std::vector<int> balls_to_remove;

  /*
  GLfloat light_position[] = {0.0, 0.0, 0.0, 1.0};
  
  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
  glLightfv(GL_LIGHT0, GL_POSITION, light_position);
  glEnable(GL_COLOR_MATERIAL);
  */
  for (auto& ball : balls) {
    glPushMatrix();

    if (outSideBox(ball)) {
      GLfloat flicker = (sin(glutGet(GLUT_ELAPSED_TIME) * 0.01) + 1.0) /
                        2.0;  // 0.0 ~ 1.0 사이의 값
      glColor4f(ball.colorR * flicker, ball.colorG * flicker,
                ball.colorB * flicker, ball.colorA);
    } else {
      glColor4f(ball.colorR, ball.colorG, ball.colorB, ball.colorA);
    }

    glTranslatef(ball.x, ball.y, ball.z);
    glutSolidSphere(ball.radius, 100, 100);
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
  for (int index : balls_to_remove) {
    balls.erase(balls.begin() + index);
  }
  balls_to_remove.clear();

  int type = nextFruit[0];
  float radius = fruitSize.find(type)->second;
  float mass = fruitWeight.find(type)->second;
  GLfloat r = fruitColor.find(type)->second[0];
  GLfloat g = fruitColor.find(type)->second[1];
  GLfloat b = fruitColor.find(type)->second[2];
  GLfloat a = fruitColor.find(type)->second[3];


  glColor4f(r,g,b,a); 
  glPushMatrix();
  glTranslatef(marker_x, marker_y, marker_z);
  glutSolidSphere(radius, 20, 20);  // 여기에 앞으로 떨굴 공을 표시
  glPopMatrix();

  glColor3f(1.0f, 0.0f, 0.0f);
  glBegin(GL_LINES);
  glVertex3f(marker_x, -2.0f, marker_z);  // 박스 바닥부터 천장까지 이어줌
  glVertex3f(marker_x, 2.0f, marker_z);
  glEnd();

  glColor3f(1.0f, 1.0f, 1.0f);  // 다시 흰색으로 복구
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
    float radius = fruitSize.find(type)->second;
    float mass = fruitWeight.find(type)->second;
    GLfloat r = fruitColor.find(type)->second[0];
    GLfloat g = fruitColor.find(type)->second[1];
    GLfloat b = fruitColor.find(type)->second[2];
    GLfloat a = fruitColor.find(type)->second[3];

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

    glPushMatrix();
    glColor4f(r, g, b, a);
    glTranslatef(0, 13-i, 0);

    glutSolidSphere(radius, 100, 100);
    glPopMatrix();


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
    float radius = fruitSize.find(type)->second;
    float mass = fruitWeight.find(type)->second;
    GLfloat r = fruitColor.find(type)->second[0];
    GLfloat g = fruitColor.find(type)->second[1];
    GLfloat b = fruitColor.find(type)->second[2];
    GLfloat a = fruitColor.find(type)->second[3];


    glColor4f(r, g, b, a);
    glPushMatrix();
    glTranslatef(0, 20, 0);
    glutSolidSphere(radius, 20, 20); 
    glPopMatrix();

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
  gluOrtho2D(0.0, window_width, 0.0,
             window_height);  // Set up an orthographic projection
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