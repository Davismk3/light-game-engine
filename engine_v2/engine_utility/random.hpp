#pragma once

#include <random>
#include <cmath>
#include <cstdint>

float randomFloat(float upper, float lower);
float hash11(float x, float y, float z, int seed);  // Hash11 (Deterministically Random Number) [-1.0, 1.0]
float valueNoiseSingle(float x, float y, float z, int seed);  // Value Noise Single Pass
float valueNoiseDouble(float x, float y, float z, int seed);  // Value Noise Double Pass
float brownianNoise(  // Brownian Noise [-1.0, 1.0]
    int x,
    int y,
    int z,
    int seed,
    int octaves = 1,
    float persistence = 0.5f,
    float lacunarity = 2.0f,
    float scale = 0.01f
);
