#include "Ball.h"

std::random_device rd;  // 랜덤한 숫자를 생성하기 위한 장치
std::mt19937 gen(rd());  // 메르센 트위스터 알고리즘을 이용한 난수 생성기
std::uniform_int_distribution<> dis(0, 4);  // 0에서 4 사이의 균일 분포

map<int, float> fruitSize;
map<int, float> fruitWeight;
map<int, std::vector<GLfloat>> fruitColor;
vector<int> nextFruit;

int hold = -1;

void fruits() { 
  fruitSize.insert(make_pair(0, 0.1));
  fruitSize.insert(make_pair(1, 0.15));
  fruitSize.insert(make_pair(2, 0.25));
  fruitSize.insert(make_pair(3, 0.3));
  fruitSize.insert(make_pair(4, 0.35));
  fruitSize.insert(make_pair(5, 0.4));
  fruitSize.insert(make_pair(6, 0.5));
  fruitSize.insert(make_pair(7, 0.6));
  fruitSize.insert(make_pair(8, 0.8));
  fruitSize.insert(make_pair(9, 1.0));
  fruitSize.insert(make_pair(10, 1.2));
  

  fruitWeight.insert(make_pair(0, 1));
  fruitWeight.insert(make_pair(1, 3.37));
  fruitWeight.insert(make_pair(2, 8));
  fruitWeight.insert(make_pair(3, 27));
  fruitWeight.insert(make_pair(4, 1));
  fruitWeight.insert(make_pair(5, 64));
  fruitWeight.insert(make_pair(6, 125));
  fruitWeight.insert(make_pair(7, 216));
  fruitWeight.insert(make_pair(8, 400));
  fruitWeight.insert(make_pair(9, 1000));
  fruitWeight.insert(make_pair(10, 1400));

  fruitColor.insert(
      std::make_pair(0, std::vector<GLfloat>{1.0f, 0.0f, 0.0f, 1.0f})); 
  fruitColor.insert(
      std::make_pair(1, std::vector<GLfloat>{1.0f, 0.2f, 0.3f, 1.0f})); 
  fruitColor.insert(
      std::make_pair(2, std::vector<GLfloat>{0.5f, 0.0f, 0.5f, 1.0f})); 
  fruitColor.insert(
      std::make_pair(3, std::vector<GLfloat>{1.0f, 0.5f, 0.0f, 1.0f})); 
  fruitColor.insert(
      std::make_pair(4, std::vector<GLfloat>{1.0f, 0.6f, 0.0f, 1.0f}));
  fruitColor.insert(
      std::make_pair(5, std::vector<GLfloat>{0.0f, 1.0f, 0.0f, 1.0f})); 
  fruitColor.insert(
      std::make_pair(6, std::vector<GLfloat>{0.8f, 1.0f, 0.2f, 1.0f})); 
  fruitColor.insert(
      std::make_pair(7, std::vector<GLfloat>{1.0f, 0.9f, 0.7f, 1.0f})); 
  fruitColor.insert(std::make_pair(8, std::vector<GLfloat>{0.6f, 0.4f, 0.1f, 1.0f})); 
  fruitColor.insert(
      std::make_pair(9, std::vector<GLfloat>{0.5f, 1.0f, 0.5f, 1.0f})); 
  fruitColor.insert(
      std::make_pair(10, std::vector<GLfloat>{0.0f, 0.5f, 0.0f, 1.0f}));

  nextFruit.push_back(dis(gen));
  nextFruit.push_back(dis(gen));
  nextFruit.push_back(dis(gen));
  nextFruit.push_back(dis(gen));
  nextFruit.push_back(dis(gen));
}
void addFruit() { 
    nextFruit.push_back(dis(gen)); 
}

Ball::Ball() {

}

/*
0 체리		0.1
1 딸기		0.15
2 포도		0.25
3 오렌지	0.3
4 감		0.35
5 사과		0.4
6 배		0.5
7 복숭아    0.6
8 파인애플  0.8
9 메론      1.0
10 수박     1.2
11 ?
*/