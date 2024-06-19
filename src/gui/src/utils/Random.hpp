/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** Random
*/

#ifndef RANDOM_HPP_
#define RANDOM_HPP_

#include <stdlib.h>

class Random {
    public:
        Random() {}
        ~Random() {}

        static int random(int min, int max) {
            return rand() % (max - min + 1) + min;
        }
        static float random(float min, float max) {
            return (rand() / (float)RAND_MAX) * (max - min) + min;
        }
        static bool randomBool() {
            return rand() % 2;
        }
    protected:
    private:
};

#endif /* !RANDOM_HPP_ */
