/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** PerlinNoise
*/

#ifndef PERLINNOISE_HPP_
#define PERLINNOISE_HPP_

#include <vector>
#include <iostream>
#include <cmath>
#include <algorithm>
#include <numeric>

class PerlinNoise {
    public:
        PerlinNoise() {
            for (int i = 0; i < 256; i++)
                _p.push_back(i);
            std::random_shuffle(_p.begin(), _p.end());
            for (int i = 0; i < 256; i++)
                _p.push_back(_p[i]);
        }
        ~PerlinNoise() {
        }

        float noise(float x, float y) {
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

        float fade(float t) {
            return t * t * t * (t * (t * 6 - 15) + 10);
        }

        float lerp(float t, float a, float b) {
            return a + t * (b - a);
        }

        float grad(int hash, float x, float y) {
            int h = hash & 15;
            float u = h < 8 ? x : y;
            float v = h < 4 ? y : h == 12 || h == 14 ? x : 0;
            return ((h & 1) == 0 ? u : -u) + ((h & 2) == 0 ? v : -v);
        }

    protected:
    private:
        std::vector<int> _p;
};

#endif /* !PERLINNOISE_HPP_ */
