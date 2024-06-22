#include "PerlinNoise.hpp"

#include <cmath>
#include <algorithm>

float PerlinNoise::noise(float x, float y) {
    int X = (int)floor(x) & 255;
    int Y = (int)floor(y) & 255;
    x -= floor(x);
    y -= floor(y);
    float u = fade(x);
    float v = fade(y);
    int A = _p[X] + Y;
    int AA = _p[A];
    int AB = _p[A + 1];
    int B = _p[X + 1] + Y;
    int BA = _p[B];
    int BB = _p[B + 1];
    return lerp(v, lerp(u, grad(_p[AA], x, y),
        grad(_p[BA], x - 1, y)),
        lerp(u, grad(_p[AB], x, y - 1),
            grad(_p[BB], x - 1, y - 1)));
}

float PerlinNoise::fade(float t) {
    return t * t * t * (t * (t * 6 - 15) + 10);
}

float PerlinNoise::lerp(float t, float a, float b) {
    return a + t * (b - a);
}

float PerlinNoise::grad(int hash, float x, float y) {
    int h = hash & 15;
    float u = h < 8 ? x : y;
    float v = h < 4 ? y : h == 12 || h == 14 ? x : 0;
    return ((h & 1) == 0 ? u : -u) + ((h & 2) == 0 ? v : -v);
}

void PerlinNoise::initPermutationVector(unsigned int seed) {
    _p.clear();
    for (int i = 0; i < 256; ++i) _p.push_back(i);
    std::shuffle(_p.begin(), _p.end(), std::default_random_engine(seed));
    for (int i = 0; i < 256; ++i) _p.push_back(_p[i]);
}
