#include "random_generator.h"

std::random_device RandomGenerator::rd;
std::mt19937 RandomGenerator::gen(rd());
std::uniform_real_distribution<float> RandomGenerator::dist(0.0, 1.0);

float RandomGenerator::getRandomNumber() {
    return dist(gen);
}