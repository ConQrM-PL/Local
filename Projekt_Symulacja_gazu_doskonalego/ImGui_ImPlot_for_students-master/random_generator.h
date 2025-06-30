#pragma once

#include <random>

//use RandomGenerator::getRandomNumber() for a random number anywhere

class RandomGenerator {
public:
    static std::random_device rd;
    static std::mt19937 gen;
    static std::uniform_real_distribution<float> dist;
    
    static float getRandomNumber();
};