/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** PerlinNoise
*/

#ifndef PERLINNOISE_HPP_
    #define PERLINNOISE_HPP_

    #include <vector>
    #include <cmath>
    #include <algorithm>
    #include <numeric>
    #include <random>

class PerlinNoise {
    public:

        PerlinNoise(unsigned int seed = std::random_device{}()) {
            initPermutationVector(seed);
        }
        ~PerlinNoise() {};

        float noise(float x, float y);
        float fade(float t);

        float lerp(float t, float a, float b);

        float grad(int hash, float x, float y);
    protected:
    private:
        std::vector<int> _p;
        void initPermutationVector(unsigned int seed);
};

#endif /* !PERLINNOISE_HPP_ */
