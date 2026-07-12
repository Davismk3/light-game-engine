#include "random.hpp"

float randomFloat(float upper, float lower) {
    static std::random_device rd;  // random seed from the hardware
    static std::mt19937 gen(rd());
    std::uniform_real_distribution<float> distrib(lower, upper);
    return distrib(gen);
}
