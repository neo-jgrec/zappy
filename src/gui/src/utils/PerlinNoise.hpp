/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** PerlinNoise
*/

#ifndef PERLINNOISE_HPP_
    #define PERLINNOISE_HPP_

    #include <vector>

class PerlinNoise {
    public:
        PerlinNoise();
        ~PerlinNoise() {};

        float noise(float x, float y);
        float fade(float t);

        float lerp(float t, float a, float b);

        float grad(int hash, float x, float y);
    protected:
    private:
        std::vector<int> _p;
};

#endif /* !PERLINNOISE_HPP_ */
