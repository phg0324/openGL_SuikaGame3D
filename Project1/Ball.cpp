#include "Ball.h"

std::default_random_engine generator;
std::uniform_real_distribution<float> radiusDistribution(0.1f, 0.5f);

Ball::Ball() {

	radius = radiusDistribution(generator); 
}